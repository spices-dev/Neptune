solution.DefineCStaticLibrary("Glad", function()

    systemversion "latest"

	files
	{
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }
    
    externalincludedirs
    {
        "include/glad",                            -- Library: Glad Source Folder.
    }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

end)