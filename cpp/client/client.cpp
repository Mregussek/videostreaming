#include "src/network.h"
#include "src/displayer.h"

int main()
{
    Network connection = Network();
    connection.defSocket();
    connection.defSockaddr();
    connection.connectToServer();

    Displayer display = Displayer();
    display.checkIfContinuous();
    std::cout << "Image Size:" << display.getImageSize() << std::endl;
    display.createWindow();

    uchar* metadata = display.getMetadata();

    while (display.getKey() != 'q')
    {
        connection.receiveData(metadata, display.getImageSize());
        
        display.showImage();
      
        if (display.wait() >= 0)
            break;
    }   

    connection.closeConnection();

    return 0;
}	