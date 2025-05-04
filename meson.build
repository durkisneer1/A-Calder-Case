project(
    'Noir Jam Game',
    'cpp',
    default_options: ['cpp_std=c++17', 'default_library=static'],
)

kraken_proj = subproject('kraken-engine')
kraken_dep = kraken_proj.get_variable('kraken_engine_dep')

json_proj = subproject('nlohmann_json')
json_dep = json_proj.get_variable('nlohmann_json_dep')

inc = include_directories('include')
subdir('src')

executable(
    'app',
    src + 'main.cpp',
    include_directories: inc,
    dependencies: [kraken_dep, json_dep],
)