#///////////////////////////////////////////////////////////////////////////
#/
#/  VLib Source File.
#/  Copyright (C) 2024 S/N: V-01
#/ -------------------------------------------------------------------------
#/  File name:   xrmyth_generate.py
#/  Version:     v1.00
#/  Created:     31/07/24 by V.
#/  Description: 
#/ -------------------------------------------------------------------------
#/  This project is licensed under the MIT License
#/
#///////////////////////////////////////////////////////////////////////////

from collections import OrderedDict
import re
import sys
import xml.etree.ElementTree as etree

def is_descendant_type(types, name, base):
	if name == base:
		return True
	type = types.get(name)
	if not type:
		return False
	parents = type.get('parent')
	if not parents:
		return False
	return any([is_descendant_type(types, parent, base) for parent in parents.split(',')])

def defined(Key):
    return "defined(" + Key + ")"

def cdepends(key):
	return re.sub(r'[a-zA-Z0-9_]+', lambda m: defined(m.group(0)), key).replace(',', ' || ').replace('+', ' && ')

def patch(FileName, SourceName, Blocks):
    Result = []

    with open(SourceName, "r") as File:
        for Line in File.readlines():
            Result.append(Line)

            if Line.strip().startswith("//SECTION(V): XRMYTH_LOAD_BASIC"):
                Result.append(Blocks["LOAD_LOADER"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_LOAD_INSTANCE"):
                Result.append(Blocks["LOAD_INSTANCE"])

            if Line.strip().startswith("//SECTION(V): XR_PROTOTYPE_HEADER"):
                Result.append(Blocks["PROTOTYPE_H"])

            if Line.strip().startswith("//SECTION(V): TEX_PARSER_XR_PROTOTYPES"):
                Result.append(Blocks["PROTOTYPE_H"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_PROTOTYPE_IMPL"):
                Result.append(Blocks["PROTOTYPE_C"])

    with open(FileName, "w", newline = "\n") as File:
        for Line in Result:
            File.write(Line)

def generate():
    print("Generating openxr loader")

    Spec = etree.parse(sys.argv[1])

    CommandGroups = OrderedDict()
    InstanceCommands = set()

    for Feature in Spec.findall("feature"):
        Key = defined(Feature.get("name"))
        CmdRefs = Feature.findall("require/command")
        CommandGroups[Key] = [CmdRef.get("name") for CmdRef in CmdRefs]

    #print(CommandGroups)

    for Ext in sorted(Spec.findall("extensions/extension"), key = lambda Ext: Ext.get("name")):
        Supported = Ext.get("supported")
        if "openxr" not in Supported.split(","):
            continue

        Name = Ext.get("name")
        Type = Ext.get("type")

        #print(Name + " " + Type)

        for Req in Ext.findall("require"):
            Key = defined(Name)
            if Req.get("feature"):
                for i in Req.get("feature").split(","):
                    Key += " && " + defined(i)
            
            if Req.get("extension"):
                for i in Req.get("extension").split(","):
                    Key += " && " + defined(i)

            if Req.get("depends"):
                Dep = cdepends(Req.get("depends"))
                Key += " && " + ("(" + Dep + ")" if "||" in Dep else Dep)
            
            CmdRefs = Req.findall("command")
            for CmdRef in CmdRefs:
                CommandGroups.setdefault(Key, []).append(CmdRef.get("name"))

            if Type == "instance":
                for CmdRef in CmdRefs:
                    InstanceCommands.add(CmdRef.get("name"))

    #print(CommandGroups)
    #print(InstanceCommands)

    Commands = {}

    for Cmd in Spec.findall("commands/command"):
        if not Cmd.get("alias"):
            Name = Cmd.findtext("proto/name")
            Commands[Name] = Cmd

    for Cmd in Spec.findall("commands/command"):
        if Cmd.get("alias"):
            Name = Cmd.get("name")
            Commands[Name] = Commands[Cmd.get("alias")]

    #print(Commands)

    Types = {}
    for Type in Spec.findall("types/type"):
        Name = Type.findtext("name")
        if Name:
            Types[Name] = Type

    #print(Types)

    Blocks = {}
    BlockKeys = {"PROTOTYPE_H", "PROTOTYPE_C", "LOAD_LOADER", "LOAD_INSTANCE"}

    for Key in BlockKeys:
        Blocks[Key] = ""

    for (Group, CmdNames) in CommandGroups.items():
        Ifdef = "#if " + Group + "\n"

        for Key in BlockKeys:
            Blocks[Key] += Ifdef

        for Name in sorted(CmdNames):
            Cmd = Commands[Name]
            Type = Cmd.findtext("param[1]/type")

            if Name == "xrGetInstanceProcAddr":
                Type = ""

# is_descendant_type(Types, Type, "XrInstance") and Name not in InstanceCommands

            if Name.startswith("xrCreateInstance") or Name.startswith("xrEnumerateApiLayerProperties") or Name.startswith("xrEnumerateInstanceExtensionProperties"):
                Blocks["LOAD_LOADER"] += "    " + Name + " = (PFN_" + Name + ')LoadFunc(Instance, "' + Name + '");\n'

            elif Type != "":
                Blocks["LOAD_INSTANCE"] += "    " + Name + " = (PFN_" + Name + ')LoadFunc(Instance, "' + Name + '");\n'
            
            Blocks["PROTOTYPE_H"] += "extern PFN_" + Name + " " + Name + ";\n"
            Blocks["PROTOTYPE_C"] += "PFN_" + Name + " " + Name + ";\n"

        for Key in BlockKeys:
            if Blocks[Key].endswith(Ifdef):
                Blocks[Key] = Blocks[Key][:-len(Ifdef)]
            else:
                Blocks[Key] += "#endif /*  " + Group + "   */\n"

    #print(Blocks)
    
    patch(sys.argv[2], sys.argv[4], Blocks)
    patch(sys.argv[3], sys.argv[5], Blocks)

generate()
