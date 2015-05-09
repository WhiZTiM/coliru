#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

int main()
{
    std::string const strXMLText = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?> 
    <NotificationSet vers="1.0" svcid="session" notid="42">
        <Notification><SessionNotification vers="1.0" notid="42">
                <Session sid="sdfkljdsfkjjsf" stype="user" cid="uid=1,u=People,dc=r,dc=c" cd="o=rrs,o=ces,maxtime=64" maxidle="24">
                    <Property name="CharSet" value="UTF-8"></Property>
                    <Property name="ed" value="xxx"></Property>
                    <Property name="Sdle" value="sdl:asdadsad"></Property>
                </Session>
                <Type>5</Type>
                <Time>324242</Time>
        </SessionNotification></Notification>
    </NotificationSet>
    )";

    //// Parse the HTTP header Status line.
    std::stringstream ss(strXMLText);

    boost::property_tree::ptree xmlResponse;

    std::istringstream isResponse (strXMLText);
    boost::property_tree::read_xml(isResponse, xmlResponse);

    if (auto SessionNotification = xmlResponse.get_child_optional("NotificationSet.Notification.SessionNotification"))
    {
        struct SessionElement {
            std::string id;
            unsigned int uiTypeOfNotification;
        };
        
        if (auto Session = SessionNotification->get_child_optional("Session")) {
            SessionElement elem {
                Session->get("<xmlattr>.sid", ""),
                SessionNotification->get("Type", 0u)
            };

            std::cout << "id: " << elem.id << ", type: " << elem.uiTypeOfNotification << "\n";
        }
    }
}
