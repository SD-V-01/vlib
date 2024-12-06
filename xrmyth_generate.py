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

def patch(FileName, SourceName, Blocks, EnumBlocks, SpecialEnumsBlocks):
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

            if Line.strip().startswith("//SECTION(V): XRMYTH_TOSTR8_IMPL"):
                Result.append(EnumBlocks["VSTR8_IMPL"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_TOSTR8_PROTO"):
                Result.append(EnumBlocks["VSTR8_PROTO"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_TOSTR32_IMPL"):
                Result.append(EnumBlocks["VSTR32_IMPL"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_TOSTR32_PROTO"):
                Result.append(EnumBlocks["VSTR32_PROTO"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_SPECIAL_ENUM8_PROTO"):
                Result.append(SpecialEnumsBlocks["VSTR8_SPEC_PROTO"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_SPECIAL_ENUM32_PROTO"):
                Result.append(SpecialEnumsBlocks["VSTR32_SPEC_PROTO"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_SPECIAL_ENUM8_IMPL"):
                Result.append(SpecialEnumsBlocks["VSTR8_SPEC_IMPL"])

            if Line.strip().startswith("//SECTION(V): XRMYTH_SPECIAL_ENUM32_IMPL"):
                Result.append(SpecialEnumsBlocks["VSTR32_SPEC_IMPL"])

    with open(FileName, "w", newline = "\n") as File:
        for Line in Result:
            File.write(Line)

def generate():
    #print("Generating openxr loader")

    Spec = etree.parse(sys.argv[1])

    CommandGroups = OrderedDict()
    EnumGroups = OrderedDict()
    InstanceCommands = set()

    SpecialEnumGroups = OrderedDict()
    SpecialEnumsCons = {"XrStructureType", "XrObjectType", "XrResult", "XrReferenceSpaceType", "XrPassthroughLayerPurposeFB", "XrSpaceComponentTypeFB", "XrViewConfigurationType", "XrSceneComputeFeatureMSFT", "XrSceneComponentTypeMSFT", "XrHandJointSetEXT"}

    for Feature in Spec.findall("feature"):
        Key = defined(Feature.get("name"))
        CmdRefs = Feature.findall("require/command")
        CommandGroups[Key] = [CmdRef.get("name") for CmdRef in CmdRefs]

    #print(CommandGroups)

    for Feature in Spec.findall("feature"):
        Key = defined(Feature.get("name"))
        EnumRefs = Feature.findall("require/type")
        EnumGroups[Key] = [CmdRef.get("name") for CmdRef in EnumRefs]

    #for Feature in Spec.findall("feature"):
    #    Key = defined(Feature.get("name"))
    #    EnumRefs = Feature.findall("require/enum")
    #    print(Key)
    #    print(CmdRef.get("name") for CmdRef in EnumRefs)

    #for SpecEnum in SpecialEnumsCons:
    #    for AllEnums in Spec.findall("enums"):
    #        if SpecEnum == AllEnums.get("name"):
    #            Key = defined("XR_VERSION_1_0")
    #            #SpecialEnumGroups[Key] = [IEnum for IEnum in AllEnums.findall("enum")]
    #            for IEnum in AllEnums.findall("enum"):
    #                #print(IEnum.get("name"))
    #                SpecialEnumGroups.setdefault(Key, []).append(IEnum)

    #print(EnumGroups)
    #print(SpecialEnumGroups)

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

            EnumRefs = Req.findall("type")
            for EnumRef in EnumRefs:
                EnumGroups.setdefault(Key, []).append(EnumRef.get("name"))

            for SpecEnum in Req.findall("enum"):
                if SpecEnum.get("extends") != None:
                    #print(SpecEnum.get("extends"))
                    if SpecEnum.get("alias") == None:
                        SpecialEnumGroups.setdefault(Key, []).append((SpecEnum.get("name"), SpecEnum.get("extends")))
                    #SpecialEnumGroups.setdefault(Key, []).append((SpecEnum.get("name"), SpecEnum.get("extends")))

            if Type == "instance":
                for CmdRef in CmdRefs:
                    InstanceCommands.add(CmdRef.get("name"))

    #print(CommandGroups)
    #print(InstanceCommands)
    #print(EnumGroups)
    #print(SpecialEnumGroups)


    Enums = {}

    for Enum in Spec.findall("enums"):
        if Enum.get("type") != "enum":
            continue
        #print(Enum.get("name"))
        Name = Enum.get("name")
        Enums[Name] = Enum

    #print(Enums)

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

    EnumBlocks = {}
    EnumKeys = {"VSTR8_IMPL", "VSTR8_PROTO", "VSTR32_PROTO", "VSTR32_IMPL"}

    for Key in EnumKeys:
        EnumBlocks[Key] = ""

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

    #for Enum in Spec.findall("enums"):
        #print(Enum.get("name"))

    SpecEnumGlobalDefine = {}

    for (Group, EnumName) in EnumGroups.items():
        #print(Group)
        #print(EnumName)

        Ifdef = "#if " + Group + "\n"

        for Key in EnumKeys:
            EnumBlocks[Key] += Ifdef

        for Enum in EnumName:
            #print(Enum)
            ShouldRun = True
            for Avoid in SpecialEnumsCons:
                if Enum == Avoid:
                    #print(Ifdef)
                    SpecEnumGlobalDefine[Enum] = Group
                    ShouldRun = False
            if ShouldRun == False:
                continue
                
            if Enums.get(Enum) != None:
                EnumBlocks["VSTR8_PROTO"] += "const char* vtostr8_" + Enum + "(" + Enum + " In);\n"
                EnumBlocks["VSTR32_PROTO"] += "const vchar* vtostr32_" + Enum + "(" + Enum + " In);\n"
                EnumBlocks["VSTR8_IMPL"] += "const char* vtostr8_" + Enum + "(" + Enum + " In){\n"
                EnumBlocks["VSTR8_IMPL"] += "    switch(In){\n\n"

                for Case in Enums[Enum].findall("enum"):
                    CaseName = Case.get("name")
                    EnumBlocks["VSTR8_IMPL"] += "    case(" + CaseName + "):\n"
                    EnumBlocks["VSTR8_IMPL"] += '        return "' + CaseName + '";\n        break;\n'

                EnumBlocks["VSTR8_IMPL"] += '    default:\n        return "' + Enum + '_TOSTR_ERROR";\n\n    }\n'

                EnumBlocks["VSTR8_IMPL"] += "\n}\n\n"

                EnumBlocks["VSTR32_IMPL"] += "const vchar* vtostr32_" + Enum + "(" + Enum + " In){\n"
                EnumBlocks["VSTR32_IMPL"] += "    switch(In){\n\n"

                for Case in Enums[Enum].findall("enum"):
                    CaseName = Case.get("name")
                    EnumBlocks["VSTR32_IMPL"] += "    case(" + CaseName + "):\n"
                    EnumBlocks["VSTR32_IMPL"] += '        return U"' + CaseName + '";\n        break;\n'

                EnumBlocks["VSTR32_IMPL"] += '    default:\n        return U"' + Enum + '_TOSTR_ERROR";\n\n    }\n'

                EnumBlocks["VSTR32_IMPL"] += "\n}\n\n"

        for Key in EnumKeys:
            if EnumBlocks[Key].endswith(Ifdef):
                EnumBlocks[Key] = EnumBlocks[Key][:-len(Ifdef)]
            else:
                EnumBlocks[Key] += "#endif /*  " + Group + "  */\n"

    SpecialEnumBlocks = {}
    EnumKeys = {"VSTR8_SPEC_IMPL", "VSTR8_SPEC_PROTO", "VSTR32_SPEC_PROTO", "VSTR32_SPEC_IMPL"}

    for EnumKey in EnumKeys:
        SpecialEnumBlocks[EnumKey] = ""

    for SpecialEnum in SpecialEnumsCons:
        #print(SpecialEnum)
        if SpecEnumGlobalDefine.get(SpecialEnum) != None:
            SpecialEnumBlocks["VSTR8_SPEC_PROTO"] += "#if " + SpecEnumGlobalDefine.get(SpecialEnum) + "\n"
            SpecialEnumBlocks["VSTR32_SPEC_PROTO"] += "#if " + SpecEnumGlobalDefine.get(SpecialEnum) + "\n"

        SpecialEnumBlocks["VSTR8_SPEC_PROTO"] += "const char* vtostr8_" + SpecialEnum + "(" + SpecialEnum + " In);\n"
        SpecialEnumBlocks["VSTR32_SPEC_PROTO"] += "const vchar* vtostr32_" + SpecialEnum + "(" + SpecialEnum + " In);\n"

        if SpecEnumGlobalDefine.get(SpecialEnum) != None:
            SpecialEnumBlocks["VSTR8_SPEC_PROTO"] += "#endif\n"
            SpecialEnumBlocks["VSTR32_SPEC_PROTO"] += "#endif\n"

        if SpecEnumGlobalDefine.get(SpecialEnum) != None:
            SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "#if " + SpecEnumGlobalDefine.get(SpecialEnum) + "\n"

        SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "const char* vtostr8_" + SpecialEnum + "(" + SpecialEnum + " In){\n"
        SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "    switch(In){\n"

        #print(Spec.find('enums[name="' + SpecialEnum + '"]'))
        for GlobalEnum in Spec.findall("enums"):
            if GlobalEnum.get("name") == SpecialEnum:
                for GlobalVal in GlobalEnum.findall("enum"):
                    SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "    case(" + GlobalVal.get("name") + "):\n"
                    SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += '        return "' + GlobalVal.get("name") + '";\n        break;\n'

        for (Group, Enums) in SpecialEnumGroups.items():
            Ifdef = "#if " + Group + "\n"
            SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += Ifdef

            for Enum in Enums:
                if Enum[1] == SpecialEnum:
                    #print(Enum)
                    SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "    case(" + Enum[0] + "):\n"
                    SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += '        return "' + Enum[0] + '";\n        break;\n'

            if SpecialEnumBlocks["VSTR8_SPEC_IMPL"].endswith(Ifdef):
                SpecialEnumBlocks["VSTR8_SPEC_IMPL"] = SpecialEnumBlocks["VSTR8_SPEC_IMPL"][:-len(Ifdef)]
            else:
                SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "#endif /*  " + Group + "  */\n"

        SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += '    default:\n        return "' + SpecialEnum + '_TOSTR_ERROR";\n\n    }\n\n}\n\n'

        if SpecEnumGlobalDefine.get(SpecialEnum) != None:
            SpecialEnumBlocks["VSTR8_SPEC_IMPL"] += "#endif\n\n"


        if SpecEnumGlobalDefine.get(SpecialEnum) != None:
            SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "#if " + SpecEnumGlobalDefine.get(SpecialEnum) + "\n"

        SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "const vchar* vtostr32_" + SpecialEnum + "(" + SpecialEnum + " In){\n"
        SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "    switch(In){\n"

        #print(Spec.find('enums[name="' + SpecialEnum + '"]'))
        for GlobalEnum in Spec.findall("enums"):
            if GlobalEnum.get("name") == SpecialEnum:
                for GlobalVal in GlobalEnum.findall("enum"):
                    SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "    case(" + GlobalVal.get("name") + "):\n"
                    SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += '        return U"' + GlobalVal.get("name") + '";\n        break;\n'

        for (Group, Enums) in SpecialEnumGroups.items():
            Ifdef = "#if " + Group + "\n"
            SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += Ifdef

            for Enum in Enums:
                if Enum[1] == SpecialEnum:
                    #print(Enum)
                    SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "    case(" + Enum[0] + "):\n"
                    SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += '        return U"' + Enum[0] + '";\n        break;\n'

            if SpecialEnumBlocks["VSTR32_SPEC_IMPL"].endswith(Ifdef):
                SpecialEnumBlocks["VSTR32_SPEC_IMPL"] = SpecialEnumBlocks["VSTR32_SPEC_IMPL"][:-len(Ifdef)]
            else:
                SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "#endif /*  " + Group + "  */\n"

        SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += '    default:\n        return U"' + SpecialEnum + '_TOSTR_ERROR";\n\n    }\n\n}\n\n'

        if SpecEnumGlobalDefine.get(SpecialEnum) != None:
            SpecialEnumBlocks["VSTR32_SPEC_IMPL"] += "#endif\n\n"


    #for (Group, AttrName) in SpecialEnumGroups.items():
    #    print(Group)
    #    print(AttrName)

    #print(SpecEnumGlobalDefine)
    #print(Blocks)
    #print(EnumBlocks)
    
    patch(sys.argv[2], sys.argv[4], Blocks, EnumBlocks, SpecialEnumBlocks)
    patch(sys.argv[3], sys.argv[5], Blocks, EnumBlocks, SpecialEnumBlocks)

generate()
