-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

-- OverLoad os.target() in android for premake do not support it.
if _ACTION == "androidndk" then
	os.target = function() return "android" end
end

			     require "androidndk"
solution       = require "solution"
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

solution.LoadProjects()

vendor.LoadThirdPartyProjects()