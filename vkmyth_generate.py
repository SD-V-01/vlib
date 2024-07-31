#///////////////////////////////////////////////////////////////////////////
#/
#/  VLib Source File.
#/  Copyright (C) 2024 S/N: V-01
#/ -------------------------------------------------------------------------
#/  File name:   vkmyth_generate.py
#/  Version:     v1.00
#/  Created:     29/07/24 by V.
#/  Description: 
#/ -------------------------------------------------------------------------
#/  This project is licensed under the MIT License
#/
#///////////////////////////////////////////////////////////////////////////

import sys
import xml.etree.ElementTree as etree
from collections import OrderedDict
import re

CmdVersions = {
	"vkCmdSetDiscardRectangleEnableEXT": 2,
	"vkCmdSetDiscardRectangleModeEXT": 2,
	"vkCmdSetExclusiveScissorEnableNV": 2
}

def patch(FileName, SourceFile, Blocks):
    Result = []
    Block = None

    with open(SourceFile, "r") as File:
        for Line in File.readlines():
            if Block:
                if Line == Block:
                    Result.append(line)
                    Block = None

            else:
                Result.append(Line)
                if Line.strip().startswith("//SECTION(V): VK_PROTOTYPES_IMPL"):
                    #Block = Line
                    Result.append(Blocks["PROTOTYPES_C"])
                
                if Line.strip().startswith("//SECTION(V): VK_LOADER_DEVICE_ARRAY_IMPL"):
                    Result.append(Blocks["LOAD_DEVICE_TABLE"])
                
                if Line.strip().startswith("//SECTION(V): VK_LOADER_DEVICE_IMPL"):
                    Result.append(Blocks["LOAD_DEVICE"])
                
                if Line.strip().startswith("//SECTION(V): VK_LOADER_INSTANCE_IMPL"):
                    Result.append(Blocks["LOAD_INSTANCE"])
                if Line.strip().startswith("//SECTION(V): VK_LOADER_BASIC_IMPL"):
                    Result.append(Blocks["LOAD_LOADER"])
                if Line.strip().startswith("//SECTION(V): TENX_PARSER_DEVICE_FUNC_ARRAY"):
                    Result.append(Blocks["DEVICE_TABLE"])#TODO(V): Make this actually have function definitions for 10Xed
                if Line.strip().startswith("//SECTION(V): VK_DEVICE_FUNC_ARRAY"):
                    Result.append(Blocks["DEVICE_TABLE"])
                if Line.strip().startswith("//SECTION(V): TENX_PARSER_PROTOTYPES"):
                    Result.append(Blocks["PROTOTYPES_H"])
                if Line.strip().startswith("//SECTION(V): VK_PROTOTYPES_HEADER"):
                    Result.append(Blocks["PROTOTYPES_H"])

    with open(FileName, "w", newline = "\n") as File:
        for Line in Result:
            File.write(Line)

def defined(Key):
    return "defined(" + Key + ")"

def cdepends(key):
	return re.sub(r'[a-zA-Z0-9_]+', lambda m: defined(m.group(0)), key).replace(',', ' || ').replace('+', ' && ')

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

def generate():
    Spec = etree.parse(sys.argv[1])
#    Root = Spec.getroot()
#    for Child in Root:
#        print(Child.tag, Child.attrib)
    
    # Im sorry for stealing code form volk but i can't write python for the life of me !!!!!
    BlockKeys = ('DEVICE_TABLE', 'PROTOTYPES_H', 'PROTOTYPES_C', 'LOAD_LOADER', 'LOAD_INSTANCE', 'LOAD_DEVICE', 'LOAD_DEVICE_TABLE')
    Blocks = {}
    Version = Spec.find('types/type[name="VK_HEADER_VERSION"]')
    Blocks["VERSION"] = Version.find("name").tail.strip() + '\n'
    Blocks["VERSION_DEFINE"] = "#define MYTH_VK_LOADER_HEADER_VERSION " + Version.find("name").tail.strip() + '\n'

    #print(Blocks)
    CommandGroups = OrderedDict()
    InstanceCommands = set()

    for Feature in Spec.findall('feature'):
        Api = Feature.get('api')
        if 'vulkan' not in Api.split(","):
            continue
        Key = defined(Feature.get("name"))
        CmdRefs = Feature.findall("require/command")
        CommandGroups[Key] = [CmdRef.get('name') for CmdRef in CmdRefs] # I can't do this shit anymore

    #print(CommandGroups)
    
    for Ext in sorted(Spec.findall("extensions/extension"), key = lambda Ext: Ext.get("name")):
        Supported = Ext.get("supported")
        if "vulkan" not in Supported.split(","):
            continue
        
        Name = Ext.get("name")
        Type = Ext.get("type")
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

            CmdRefs = Req.findall('command')
            for CmdRef in CmdRefs:
                Ver = CmdVersions.get(CmdRef.get("name"))
                if Ver:
                    CommandGroups.setdefault(Key + " && " + Name.upper() + "_SPEC_VERSION >= " + str(Ver), []).append(CmdRef.get("name"))
                else:
                    CommandGroups.setdefault(Key, []).append(CmdRef.get("name"))

            if Type == "instance":
                for CmdRef in CmdRefs:
                    InstanceCommands.add(CmdRef.get("name"))

    #print(CommandGroups)
    #print(InstanceCommands)

    CommandToGroups = OrderedDict()

    for (Group, CmdNames) in CommandGroups.items():
        for Name in CmdNames:
            CommandToGroups.setdefault(Name, []).append(Group)

    for (Group, CmdNames) in CommandGroups.items():
        CommandGroups[Group] = [Name for Name in CmdNames if len(CommandToGroups[Name]) == 1]

    for (Name, Groups) in CommandToGroups.items():
        if len(Groups) == 1:
            continue
        Key = " || ".join(['(' + g + ')' for g in Groups])
        CommandGroups.setdefault(Key, []).append(Name)

    #print(CommandGroups)

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

    for Key in BlockKeys:
        Blocks[Key] = ""

    for (Group, CmdNames) in CommandGroups.items():
        Ifdef = "#if " + Group + "\n"

        for Key in BlockKeys:
            Blocks[Key] += Ifdef

        for Name in sorted(CmdNames):
            Cmd = Commands[Name]
            Type = Cmd.findtext("param[1]/type")

            if Name == "vkGetInstanceProcAddr":
                Type = ""
            if Name == "vkGetDeviceProcAddr":
                Type = "VkInstance"

            if is_descendant_type(Types, Type, 'VkDevice') and Name not in InstanceCommands:
                Blocks["LOAD_DEVICE"] += '    ' + Name + " = (PFN_" + Name + ')LoadFunc(Device, "' + Name + '");\n'
                Blocks["DEVICE_TABLE"] += '    PFN_' + Name + " " + Name + ';\n'
                Blocks["LOAD_DEVICE_TABLE"] += '    FuncArray->' + Name + ' = (PFN_' + Name + ')LoadFunc(Device, "' + Name + '");\n'
            elif is_descendant_type(Types, Type, 'VkInstance'):
                Blocks["LOAD_INSTANCE"] += '    ' + Name + ' = (PFN_' + Name + ')LoadFunc(Instance, "' + Name + '");\n'
            elif Type != '':
                Blocks["LOAD_LOADER"] += '    ' + Name + ' = (PFN_' + Name + ')LoadFunc(Instance, "' + Name + '");\n'

            Blocks["PROTOTYPES_H"] += "extern PFN_" + Name + " " + Name + ";\n"
            Blocks["PROTOTYPES_C"] += "PFN_" + Name + " " + Name + ";\n"

        for Key in BlockKeys:
            if Blocks[Key].endswith(Ifdef):
                Blocks[Key] = Blocks[Key][:-len(Ifdef)]
            else:
                Blocks[Key] += "#endif /*  " + Group + "  */\n"


    #print(Blocks)

    patch(sys.argv[2], sys.argv[4], Blocks)
    patch(sys.argv[3], sys.argv[5], Blocks)

generate();
