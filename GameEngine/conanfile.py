from conan import ConanFile, tools
from conan.tools.cmake import cmake_layout, CMake
from os import environ, system

class GameEngineRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    options = {
        "graphics": [True, False],
        "window": [True, False],
        "audio": [True, False],
        "system": [True, False]
    }
    default_options = {
        "graphics": True,
        "window": True,
        "audio": True,
        "system": True
    }

    def requirements(self):
        self.requires("sfml/2.6.0")
        self.requires("nlohmann_json/3.11.2")

    def layout(self):
        cmake_layout(self)

    def configure(self):
        if not self.options.graphics:
            self.options["sfml"].graphics = False
        if not self.options.window:
            self.options["sfml"].window = False
        if not self.options.audio:
            self.options["sfml"].audio = False
        if not self.options.system:
            self.options["sfml"].system = False

    def generate(self):
        include_dir = environ["INCLUDES_DIR"]
        self.output.info("Copying header files")
        libs_folder = self.build_folder + "/libs"
        tools.files.mkdir(self, include_dir)
        tools.files.mkdir(self, libs_folder)
        for require, dependency in self.dependencies.items():
            if require.direct:
                for src_dir in dependency.cpp_info.includedirs:
                    tools.files.copy(self, '*.hpp', src_dir, include_dir)
                    tools.files.copy(self, '*.inl', src_dir, include_dir)
        self.output.success("Header files copied.")
        self.output.info("Copying library files")
        for dep in self.dependencies.values():
            try:
                tools.files.copy(self, '*.dylib', dep.cpp_info.libdir, libs_folder)
                tools.files.copy(self, '*.dll', dep.cpp_info.libdir, libs_folder)
                tools.files.copy(self, '*.a', dep.cpp_info.libdir, libs_folder)
                tools.files.copy(self, '*.so', dep.cpp_info.libdir, libs_folder)
            except AssertionError:
                continue
        self.output.success("Library files copied.")

    def build(self):
        libs_folder = self.build_folder + "/libs"
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        # if self.settings.os == "Linux":
        #     system("
        # else:
        #     self.output.warning("BRUH")
