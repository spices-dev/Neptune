-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

local project  = require "project"
compiler       = require "compiler"
vendor         = require "vendor"
platform       = require "platform"

workspace "Neptune"
	startproject "Editor"              -- Start with Editor

	-- Configuration: Debug and Release.
	configurations
	{
		"Debug",
		"Release",
	}

	compiler.Initialize()
	platform.Initialize()

-- Building Output Folder.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project.Load()

vendor.LoadThirdPartyProjects()