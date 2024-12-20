/**
 *  LAUNCHPAD INIT
 *
 *  Switches a Launchpad into programmer mode as soon as it is connected.
 *
 *  Code based on the midiobserve.cpp example in the libremidi repo:
 *
 *      https://github.com/celtera/libremidi/blob/master/examples/midiobserve.cpp
 *
 *  The code sends a midi sysex message to the Launchpad to set it to
 *  programmer mode. It sends the message expected by the Launchpad X; see the
 *  programmer reference here:
 *
 *      https://fael-downloads-prod.focusrite.com/customer/prod/s3fs-public/downloads/Launchpad%20X%20-%20Programmers%20Reference%20Manual.pdf
 *
 *  The sysex message used by other Launchpad models is different - it can be
 *  found in their corresponding programmer reference manuals.
 */

#include <iostream>

#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <libremidi/libremidi.hpp>

// Allow printing port information (copied from utils.hpp in libremidi examples)

inline std::ostream &operator<<(std::ostream &s, const libremidi::port_information &rhs)
{
    s << "[ client: " << rhs.client << ", port: " << rhs.port;
    if (!rhs.manufacturer.empty())
        s << ", manufacturer: " << rhs.manufacturer;
    if (!rhs.device_name.empty())
        s << ", device: " << rhs.device_name;
    if (!rhs.port_name.empty())
        s << ", portname: " << rhs.port_name;
    if (!rhs.display_name.empty())
        s << ", display: " << rhs.display_name;
    return s << "]";
}

int main()
{
    std::vector<libremidi::observer> observers;
    for (auto api : libremidi::available_apis())
    {
        std::string_view api_name = libremidi::get_api_display_name(api);

        std::cout << "Displaying ports for: " << api_name << std::endl;
        libremidi::observer_configuration cbs;
        cbs.output_added = [=](const libremidi::output_port &p) {
            std::cout << api_name << " : output added " << p << "\n";
            if (p.port_name.find("LPX MIDI In") != std::string::npos)
            {
                std::cout << "Sending programmer mode sysex to " << p.port_name << std::endl;
                libremidi::midi_out midi;
                midi.open_port(p);
                unsigned char bytes[] = {240, 0, 32, 41, 2, 12, 14, 1, 247};
                midi.send_message(bytes, sizeof(bytes));
            }
        };
        observers.emplace_back(cbs, libremidi::observer_configuration_for(api));
        std::cout << "\n" << std::endl;
    }

    std::cout << "... waiting for hotplug events ...\n";

#if defined(__APPLE__)
    // On macOS, observation can *only* be done in the main thread
    // with an active CFRunLoop.
    CFRunLoopRun();
#elif defined(_WIN32) || defined(WIN32)
    // Windows
    system("pause");
#else
    // Linux
    pause();
#endif
    return 0;
}
