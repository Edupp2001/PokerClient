#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <thread>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Client {
private:
	SOCKET sock;

public:
	Client(string ip) {
		createclient(ip);
	}

	~Client() {
		closesocket(this->sock);
	}

	void onlytell(string msg, bool spam = false) {
		do {
			send(this->sock, msg.c_str(), msg.size(), 0);
		} while (spam);
	}

	string onlyhear(bool spam = false) {
		char buf[2000];
		memset(buf, 0, 2000);
		recv(this->sock, buf, 2000, 0);
		return buf;
	}

	string TalkToServ(string msg) {
		string data = "";
		onlytell(msg);//client speaks first
		data = onlyhear();//recieves the answer
		return data;
	}

	void createclient(string ip) {
		if (ip == "0")
			ip = "127.0.0.1";
		else if (ip == "max")
			ip = "192.168.1.240";
		WSADATA wsd;
		if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsd)))
			//Инициализация Winsock, функция WSAStartupиспользуется для указания под версии интерфейса Winsoсk
			cout << "Error with initializint winsock" << endl; //Ошибка инициализации winsock

		SOCKET sockk = socket(AF_INET, SOCK_STREAM, 0); //Создаем сокет
		if (sockk == INVALID_SOCKET)
			cout << "Error with creating socket" << endl; //Ошибка создания сокета

		sockaddr_in addr; //Создаем и заполняем переменную для хранения адреса
		addr.sin_family = AF_INET; //Семейство адресов, которые будет обрабатывать наш сервер, у нас это TCP/IP адреса
		addr.sin_port = htons(3128); //Используем функцию htons для перевода номера порта в TCP/IP представление
		addr.sin_addr.s_addr = inet_addr(ip.c_str());
		if (SOCKET_ERROR == connect(sockk, (struct sockaddr*)&addr, sizeof(addr))) //Связываем сокет с адресом
			cout << "Error with binding socket";
		this->sock = sockk;
	}

};