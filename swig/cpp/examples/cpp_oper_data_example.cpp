#include <iostream>
#include "Session.hpp"

class Cb : public sysrepo::Callback {
    int dp_get_items(const char* xpath, sysrepo::S_Vals_Holder vals, uint64_t requestId, void* ctx) override {
        std::cerr << "dp_get_items: asked for XPath " << xpath << std::endl;
        return SR_ERR_OK;
    }
};


int
main(int argc, char **argv)
{
    auto conn = std::make_shared<sysrepo::Connection>("ops-provider");
    auto session = std::make_shared<sysrepo::Session>(conn);
    auto sub = std::make_shared<sysrepo::Subscribe>(session);
    auto cb = std::make_shared<Cb>();
    sub->dp_get_items_subscribe("/dummy-amp:amplifier", cb, nullptr, SR_SUBSCR_PASSIVE | SR_SUBSCR_CTX_REUSE);

    std::string dummy;
    std::cout << "Press enter to exit this data provider..." << std::endl;
    std::getline(std::cin, dummy);
    return 0;
}
