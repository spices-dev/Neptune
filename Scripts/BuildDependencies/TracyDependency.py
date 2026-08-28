"""
@file TracyDependency.py.
@brief The TracyDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import urllib.request
import zipfile
import tarfile

"""
@brief Tracy download url.
"""
TracyURL = {
    "windows": "https://github.com/wolfpld/tracy/releases/download/v0.14.1/windows-0.14.1.zip",
    "linux":   "https://github.com/wolfpld/tracy/releases/download/v0.14.1/linux-0.14.1.zip",
    "darwin":  "https://github.com/wolfpld/tracy/releases/download/v0.14.1/macos-0.14.1.zip"
}

class TracyDependency(Dependency):
    """
    @brief Base class for solution tracy dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("tracy", ["git"])

        # Set dependency path
        if self.isWindows:
            self.dependencyPath = self.solutionDirectory / "vendor" / "tracy" /"tracy-profiler.exe"
        elif self.isMacos:
            self.dependencyPath = self.solutionDirectory / "vendor" / "tracy" /"tracy-profiler.app"

    def path(self) -> str:
        """
        @brief Get this dependency path.
        @return Returns this dependency path.
        """
        return self.dependencyPath

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        return self.dependencyPath.exists()

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """

        # Make install directory
        install_dir = self.solutionDirectory / "vendor" / "tracy"
        install_dir.mkdir(parents=True, exist_ok=True)

        try:
            url = TracyURL.get(self.system)
            if not url:
                print(f"Unsupported system for tracy auto-install: {self.system}")
                return False

            print(f"Downloading tracy from {url}")
            archive_path = install_dir / "tracy_download.zip"

            # Download the file
            urllib.request.urlretrieve(url, archive_path)

            # Extract the archive
            with zipfile.ZipFile(archive_path, 'r') as zip_ref:
                zip_ref.extractall(install_dir)

            # Clean up
            archive_path.unlink()

            return True
        except Exception as e:
            print(f"Failed to install tracy: {e}")
            return False
