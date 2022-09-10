#include <iostream>
#include "MyApp.h"

int main() {

    auto app = MyApp("Breakout", 800, 600);
    if (!app.IsInitialized()) {
        return -1;
    }

    app.Run();
}
