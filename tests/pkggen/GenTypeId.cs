﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

public static class GenTypeId
{
    public static bool Gen(Assembly asm, string outDir, string templateName)
    {
        var typeIds = new TemplateLibrary.TypeIds(asm);
        if (typeIds.typeIdMappingsExists && !typeIds.hasNewMappings) return true;

        var sb = new StringBuilder();
        sb.Append(@"#pragma warning disable 0169, 0414
using TemplateLibrary;

[TypeIdMappings]
interface ITypeIdMappings
{");
        foreach (var kv in typeIds.types)
        {
            if (kv.Key == typeof(string) || kv.Key == typeof(TemplateLibrary.BBuffer)) continue;
            var typeId = (ushort)kv.Value;
            var c = kv.Key;
            var cn = c._GetTypeDecl_Csharp();
            sb.Append(@"
    " + cn + @" _" + typeId + @" { get; }
");
        }
        sb.Append(@"
}
");
        sb._WriteToFile(Path.Combine(outDir, templateName + "_TypeIdMappings.cs"));
        return false;
    }
}
