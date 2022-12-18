#r "paket:
nuget Microsoft.Build.Framework = 16.11

nuget Fake.Core.Target
nuget Fake.DotNet.MSBuild
nuget Fake.DotNet.NuGet
nuget Fake.DotNet.Testing.XUnit2
nuget Fake.IO.Zip"

#load "./.fake/Build.fsx/intellisense.fsx"

open Fake.Core
open Fake.Core.TargetOperators
open Fake.IO
open Fake.IO.FileSystemOperators
open Fake.IO.Globbing.Operators
open Fake.DotNet
open Fake.DotNet.NuGet
open Fake.DotNet.Testing

// Directory
let buildDir86 = "./_build/x86/"
let buildDir64 = "./_build/x64/"

Target.create "Clean" (fun _ ->
    [ "./_build/"; ]
    |> Shell.cleanDirs
)

Target.create "Build86" (fun _ ->
    let x86   = [ "Platform", "x86" ]

    [ "EmbeddableCommonLispExample.sln"; ]
        |> MSBuild.runReleaseExt id buildDir86 x86 "Build"
        |> Trace.logItems "AppBuild-Output: "
)

Target.create "Build64" (fun _ ->
    let x64   = [ "Platform", "x64" ]

    [ "EmbeddableCommonLispExample.sln"; ]
        |> MSBuild.runReleaseExt id buildDir64 x64 "Build"
        |> Trace.logItems "AppBuild-Output: "
)

Target.create "Deploy" (fun _ ->
    Shell.copyDir (buildDir86 + "encodings") ("Ecl/v21.2.1/vc142-x86/encodings/") (fun _ -> true)
    Shell.copyFile buildDir86 "Ecl/v21.2.1/vc142-x86/ecl.dll"
    !! ("Script/*.*") |> Shell.copyFiles buildDir86

    Shell.copyDir (buildDir64 + "encodings") ("Ecl/v21.2.1/vc142-x64/encodings/") (fun _ -> true)
    Shell.copyFile buildDir64 "Ecl/v21.2.1/vc142-x64/ecl.dll"
    !! ("Script/*.*") |> Shell.copyFiles buildDir64
)

"Clean"
  ==> "Build86"
  ==> "Build64"
  ==> "Deploy"

Target.runOrDefault "Deploy"
