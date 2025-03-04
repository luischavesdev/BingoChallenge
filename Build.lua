-- premake5.lua
workspace "BingoChallenge"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

-- Variable is used by each project lua file
OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Bingo"
   include "Bingo/Build-Bingo.lua"
group ""

include "App/Build-App.lua"