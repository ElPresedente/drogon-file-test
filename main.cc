#include <drogon/drogon.h>
int main() {
    //Set HTTP listener address and port
    //Load config file
    drogon::app()
        .loadConfigFile("../config.json")
        .run();
    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    return 0;
}
