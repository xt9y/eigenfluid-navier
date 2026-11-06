#include <vk/vk.hpp>
#include <gpu/gpu.hpp>
#include <render/render.hpp>
#include <cstdio>

int main()
{
    gpu::buffer buffer;
    gpu::compute compute;
    render::pipeline pipeline;
    render::target target;

    if(!vk::device::get())return 1;
    std::puts("VulkanEngine, VulkanGPU and VulkanRender linked");
    return 0;
}
