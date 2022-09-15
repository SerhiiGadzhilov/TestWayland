#include <iostream>
#include <wayland-client.h>

static void registerServices(void* data,
                wl_registry* registry,
                uint32_t name,
                const char* interface,
                uint32_t version)
{
    std::cout<<"Name: "<<name<<
               "; Interface: "<<interface<<
               "; Version"<<version<<
               ";"<<std::endl;
}

static wl_registry_listener listener = {registerServices, nullptr};

int main(int argc, char *argv[])
{
    std::cout<<"Connecting to wayland display..."<<std::endl;
    auto display = wl_display_connect(nullptr);

    if (display) {
        std::cout<<"Connected to wayland display!"<<std::endl;
        auto registry = wl_display_get_registry(display);
        wl_registry_add_listener(registry, &listener, nullptr);
        wl_display_dispatch(display);

        wl_display_disconnect(display);
        std::cout<<"Disconected from wayland display!"<<std::endl;
    }
    else {
        std::cerr<<"Failed to connect to wayland display!"<<std::endl;
    }

    return 0;
}
