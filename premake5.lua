project "mavk"
	language "C"
	cdialect "C17"

	kind "StaticLib"

	files {"src/*.c"}


	filter {"configurations:debug"}
		defines {"DEBUG"}
		targetdir "./bin/debug/"
		objdir "./bin-int/debug/"
	filter {"configurations:ndebug"}
		defines {"NDEBUG"}
		targetdir "./bin"
		objdir "./bin-int/"

	filter ""
