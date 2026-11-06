#include <cbuild.h>
#include <stdio.h>
#include <stdlib.h>

static void dependencies(void)
{
    const char* paths[]={
        "third-party/vulkan-engine/build.c",
        "third-party/vulkan-systems/gpu/build.c",
        "third-party/vulkan-headers/registry/vk.xml"
    };
    for(unsigned i=0;i<sizeof(paths)/sizeof(paths[0]);++i)
    {
        FILE* file=fopen(paths[i],"r");
        if(file){fclose(file);continue;}
        if(system("git submodule update --init --recursive")!=0)
            exit(1);
        break;
    }
}

static void includes(C_Target* target)
{
    c_flag(target,"-std=c++17");
    c_include(target,"third-party/vulkan-engine");
    c_include(target,"third-party/vulkan-systems/gpu");
    c_include(target,"third-party/vulkan-systems/render");
    c_include(target,"third-party/vulkan-headers/include");
    c_include(target,"build/generated");
}

void build(C_Build* b)
{
    dependencies();

    C_Target* engine=c_static_library(b,"VulkanEngine");
    c_sources(engine,"third-party/vulkan-engine/vk/*/*.cpp");
    c_generate(engine,"build/generated/generated.cpp",
        "third-party/vulkan-headers/registry/vk.xml",
        "python3 third-party/vulkan-engine/vk/tools/generate.py "
        "third-party/vulkan-headers/registry/vk.xml "
        "build/generated/generated.hpp build/generated/generated.cpp "
        "--headers third-party/vulkan-headers/include");
    includes(engine);

    C_Target* gpu=c_static_library(b,"VulkanGPU");
    c_sources(gpu,"third-party/vulkan-systems/gpu/gpu/*.cpp");
    includes(gpu);
    c_link_target(gpu,engine);

    C_Target* render=c_static_library(b,"VulkanRender");
    c_sources(render,"third-party/vulkan-systems/render/render/*.cpp");
    includes(render);
    c_link_target(render,engine);

    C_Target* app=c_executable(b,"eigenfluid-navier");
    c_sources(app,"sources/main.cpp");
    includes(app);
    c_link_target(app,gpu);
    c_link_target(app,render);
    c_link_target(app,engine);
    c_default_target(b,app);
}
