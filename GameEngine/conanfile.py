from conan import ConanFile, tools
from conan.tools.cmake import cmake_layout
from conan.tools.microsoft import MSBuildDeps

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
        self.output.info("Copying header files")
        dest_dir = "./include"
        tools.files.mkdir(self, dest_dir)
        for require, dependency in self.dependencies.items():
            if require.direct:
                for src_dir in dependency.cpp_info.includedirs:
                    self.output.info(f"{tools.files.copy(self, '*.hpp', src_dir, dest_dir)}")
                    self.output.info(f"{tools.files.copy(self, '*.inl', src_dir, dest_dir)}")
        self.output.success("Header files copied.")
