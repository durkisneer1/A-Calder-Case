project(
    'Noir Jam Game',
    'cpp',
    default_options: ['cpp_std=c++17', 'default_library=static'],
)

add_project_arguments('-Wall', '-Wextra', '-Werror=return-type', language: 'cpp')

kraken_proj = subproject('kraken-engine')
kraken_dep = kraken_proj.get_variable('kraken_engine_dep')

inc = include_directories('include')
subdir('src')

executable(
    'app',
    src + 'main.cpp',
    include_directories: inc,
    dependencies: kraken_dep,
)