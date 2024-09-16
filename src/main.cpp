#include "application.h"
#include "platform.h"

int main() {
    cardinal::Platform platform{"Cardinal3D", {1000, 640}};
    cardinal::Application app{&platform};

    return platform.Run(app);
}