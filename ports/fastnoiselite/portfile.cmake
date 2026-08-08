vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Auburn/FastNoiseLite
    REF "v${VERSION}"
    SHA512 9eaf53d99593d7c5b60e2be1ed1e4ac274bb523bd94847b5415f22b815acbda41abdad36246fe80428c25d499a3b1a1f46e3a76ceb207ee928707c714a56bbf4
    HEAD_REF master
)

# Header-only: the C++ variant is the only file we need.
file(INSTALL "${SOURCE_PATH}/Cpp/FastNoiseLite.h"
     DESTINATION "${CURRENT_PACKAGES_DIR}/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
set(VCPKG_POLICY_EMPTY_PACKAGE enabled)
