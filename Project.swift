import ProjectDescription
import ProjectDescriptionHelpers

private let defaultPreprocessorDefinitions = [
    "AJA_MAC",
    "AJAMac",
    "AJASTATIC",
    "NTV2_PREVENT_PLUGIN_LOAD"
]

private let defaultSettings: SettingsDictionary = [
    "GCC_PREPROCESSOR_DEFINITIONS": .array(defaultPreprocessorDefinitions),
    "SRCROOT": "$(PROJECT_DIR)",
    "USER_HEADER_SEARCH_PATHS": [
        "$(PROJECT_DIR)/",
        "$(PROJECT_DIR)/ajaanc/includes/",
        "$(PROJECT_DIR)/ajantv2/includes/",
        "$(PROJECT_DIR)/ajantv2/src/mac/"
    ],
    "WARNING_CFLAGS": [
        "$(inherited)",
        "-w" // disable all warnings for AJA SDK, we won't fix them, so we don't care
    ],
    "MACOSX_DEPLOYMENT_TARGET": SettingValue(stringLiteral: Project.deploymentTarget)
]

let debugSettings = defaultSettings.merging([
    "GCC_PREPROCESSOR_DEFINITIONS": .array(defaultPreprocessorDefinitions + ["_DEBUG"])
])
let releaseSettings = defaultSettings.merging([
    "GCC_PREPROCESSOR_DEFINITIONS": .array(defaultPreprocessorDefinitions + ["NDEBUG"])
])

private let debugConf: Configuration = .debug(name: "Debug-Framework", settings: debugSettings)
private let releaseConf: Configuration = .release(name: "Release", settings: releaseSettings)

let project = Project(
    name: "libajantv2",
    settings: .settings(configurations: [debugConf, releaseConf]),
    targets: [
        Target(
            name: "libajantv2",
            destinations: [.mac],
            product: .staticLibrary,
            bundleId: "com.pomfort.libajantv2",
            infoPlist: .default,
            sources: [
                .glob("ajabase/**/*{.cpp,.c,.m,.mm,.h,.hh}", excluding: [
                            "ajabase/system/bm/**",
                            "ajabase/system/linux/**",
                            "ajabase/system/windows/**",
                            "ajabase/pnp/linux/**",
                            "ajabase/pnp/windows/**",
                            "ajabase/test/**"
                        ]),
                "ajaanc/src/**/*{.cpp,.c,.m,.mm,.h,.hh}",
                .glob("ajantv2/src/**/*{.cpp,.c,.m,.mm,.h,.hh}", excluding: [
                    "ajantv2/src/bm/**",
                    "ajantv2/src/lin/**",
                    "ajantv2/src/win/**"
                ])
            ]
        )
    ],
    additionalFiles: [
        "Project.swift"
    ]
)
