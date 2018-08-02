#include <uWS/uWS.h>
#include <iostream>

int main() {
    uWS::Hub h;

    std::string noResponse = "no response";
    std::string bffResponse = "ws://www.deuspora.com:3172";

    h.onHttpRequest([&](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t length, size_t remainingBytes)
    {
        if (req.headers->keyLength == 3 && strncmp(req.headers->key, "get", 3) == 0)
        {
            //request is a GET request
            if (req.headers->valueLength == 17 && strncmp(req.headers->value, "/orchestrator/bff", 17) == 0)
            {
                res->end(bffResponse.data(), bffResponse.length());
                std::cout << "dspr-orchestrator: Received '/orchestrator/bff', Sent " << bffResponse << std::endl;
                return;
            }
        }

        res->end(noResponse.data(), noResponse.length());
    });

    h.getDefaultGroup<uWS::SERVER>().startAutoPing(30000);
    if (h.listen("localhost", 3171)) {
        std::cout << "dspr-orchestrator: Listening to port 3171" << std::endl;
    } else {
        std::cerr << "dspr-orchestrator: Failed to listen to port" << std::endl;
        return -1;
    }

    h.run();
}
