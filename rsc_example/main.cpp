#include <iostream>
#include <iomanip>
#include <conio.h>

#include <rsc/Card.h>
#include <rsc/Readers.h>
#include <rsc/Context.h>

#include <scc/Hash.h>
#include <scc/RSA.h>
#include <scc/Exception.h>

#include <scb/ByteStream.h>

int main() {
    std::ios::sync_with_stdio(false);

    try {
        scb::Bytes modulus("AFAD7010F884E2824650F764D47D7951A16EED6DBB881F384DEDB6702E0FB55C0FBEF945A2017705E5286FA249A591E194BDCD74B21720B44CE986F144237A25F95789F38B47EA957F9ADB2372F6D5D41340A147EAC2AF324E8358AE1120EF3F");
        scb::Bytes exponent("05");

        scc::RSA rsa(modulus, exponent);

        auto result = rsa.transorm("00");
        std::cout << result << '\n';
    } catch (scc::Exception const &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        rsc::Context context(SCARD_SCOPE_USER);
        rsc::Readers readers(context, SCARD_DEFAULT_READERS);
        rsc::Card card(context, readers.list().front());
        std::cout << card.atr();
        std::cout << card.transmit(rsc::cAPDU::SELECT("A0000000031010"));
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}
