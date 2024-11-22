// SES6-02c-TCPA2-S-L.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib,"ws2_32.lib")


int main()
{
    const int PORT = 8888;
    const int MESSAGELENGTH = 512;

    SOCKET tcpSocket, connectionSocket;
    struct sockaddr_in serverAdress, clientAddress;
    int slen, recv_len;
    char message[MESSAGELENGTH];
    WSADATA wsaData;
    slen = sizeof(clientAddress);

    // Initialise Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup fehlgeschlagen: " << WSAGetLastError() << endl;
        system("pause");
        return 1;
    }

    // Create udp socket
    if ((tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        cout << "Socket erstellen fehlgeschlagen: " << WSAGetLastError() << endl;
        system("pause");
        return 1;
    }

    // set Server Parameter
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(PORT);


    // Bind socket to Port
    if (bind(tcpSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) == SOCKET_ERROR)
    {
        cout << "Binding fehlgeschlagen: " << WSAGetLastError() << endl;
        system("pause");
        return 1;
    }

    // listen
    if (listen(tcpSocket, SOMAXCONN) == INVALID_SOCKET)
    {
        cout << "Listen fehlgeschlagen: " << WSAGetLastError() << endl;
        system("pause");
        return 1;
    }

    cout << "Server gestartet." << endl;

    while (true) {

        cout << "Warte auf Verbindung." << endl;

        //Verbindung akzeptieren
        if ((connectionSocket = accept(tcpSocket, (struct sockaddr *)&clientAddress, (int *)&slen)) == INVALID_SOCKET)
        {
            cout << "Verbindung fehlgeschlagen: " << WSAGetLastError() << endl;
            system("pause");
            return 1;
        }
        cout << "Verbunden mit dem Client: " << inet_ntoa(clientAddress.sin_addr) << endl;

        // Prompt senden

        if (send(connectionSocket, "#: ", 3, 0) == SOCKET_ERROR)
        {
            cout << "Daten senden fehlgeschlagen: " << WSAGetLastError() << endl;
            system("pause");
            return 1;
        }

        while (true)
        {
            cout << "Warte auf Daten." << endl;
            fflush(stdout);

            // Daten empfangen
            memset(message, '\0', MESSAGELENGTH);
            if ((recv_len = recv(connectionSocket, message, MESSAGELENGTH, 0)) == SOCKET_ERROR)
            {
                cout << "Daten empfangen fehlgeschlagen: " << WSAGetLastError() << endl;
                system("pause");
                return 1;
            }

            cout << "Daten empfangen: " << message << endl;

            // Daten zurück senden
            if (send(connectionSocket, message, recv_len, 0) == SOCKET_ERROR)
            {
                cout << "Daten senden fehlgeschlagen: " << WSAGetLastError() << endl;
                system("pause");
                return 1;
            }

        }
        closesocket(connectionSocket);
    }
    // Close socket
    closesocket(tcpSocket);
    WSACleanup();

    system("pause");
    return 0;

}

