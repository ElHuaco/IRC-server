<div id="top"></div>
<!--
*** Amazing README template from othneildrew
*** https://github.com/othneildrew/Best-README-Template
-->


<!-- PROJECT LOGO -->
<br />
<div align="center">
  <h1>ft_irc</h1>
  <img src="https://www.plutora.com/wp-content/uploads/2018/11/irc_internet_relay_chat.png" />
</div>

<!-- ABOUT THE PROJECT -->
## ℹ️ About The Project

_42 Project_

The goal of this project is to make you write your own IRC server. To do so, you will follow the real IRC RFC and test your work with real IRC clients. Internet is ruled by solid and standards protocols that allow a strong interaction between every connected computer. It’s always good to know about it.

### Subject

* [Subject](https://cdn.intra.42.fr/pdf/pdf/32224/en.subject.pdf)

### Steps

   1. [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html//index.html)
   2. [Beej's cheesy chat example](https://beej.us/guide/bgnet/examples/selectserver.c)
   3. [RFC for Human beings](https://modern.ircdocs.horse/)
   4. ????
   5. Profit

### RFC Documentation

Request For Comments, official documentation for IRC.
  - [X] [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459)
  - [ ] [RFC 2810](https://datatracker.ietf.org/doc/html/rfc2810)
  - [ ] [RFC 2811](https://datatracker.ietf.org/doc/html/rfc2811)
  - [ ] [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)
  - [ ] [RFC 2813](https://datatracker.ietf.org/doc/html/rfc2813)
  - [ ] [RFC 7194](https://datatracker.ietf.org/doc/html/rfc7194)

### Allowed functions

<details>
  <summary>Expand</summary>
  
  - `socket()`: lo crea. Selecciona protocolos (`PF_INET` ó `PF_INET6`; `SOCK_STREAM`; `getprotobyname("tcp")`). También se puede rellenar con el `struct addrinfo` usado en `getaddrinfo()`.
  - `setsockopt()`, `getsockname()`: controlar socket descriptors, como `fcntl()`.
  - `getprotobyname()`: devuelve el número asociado al nombre del protocolo, como "tcp" o "udp".
  - `gethostbyname()`: da la dirección IP de un host name. No funciona bien con IPv6. Mejor usar `getaddrinfo()`.
  - `getaddrinfo()`, `freeaddrinfo()`: recibe información de un host name y un `struct addrinfo` con los tipos de IP y sockets a usar. Rellena el `struct sockaddr` con el resultado y crea una lista de `struct addrinfo` con las direcciones que cumplen la información pasada de argumento. Esta lista se libera con `freeaddrinfo()`.
  - `bind()`: asocia un socket con una IP y puerto.
  - `connect()`: conecta un socket a un servidor. Tras `bind()` si se queria el cliente en una IP y puerto concretos. Permite llamar a `send()` y `recv()`.
  - `listen()`: que el socket descriptor escuche conexiones entrantes. Especifica número máximo de conexiones.
  - `accept()`: acepta una conexión entrante en un listening socket. Tras haber creado un `SOCK_STREAM`y haberlo preparado para conexiones entrantes con `listen()`, llamas a esta función para crear un nuevo socket descriptor que pueda ser usado para las siguientes comunicaciones con el nuevo cliente. El socket anterior sigue estando ahí y podrá ser usado para nuevos `accept()`. Hay que `close()`este nuevo socket cuando terminemos.
  - `htons()`, `htonl()`, `ntohs()`, `ntohl()`: convierten integer types de host byte order a network byte order y viceversa, según si preparas para enviar el tipo, o lo has recibido.
  - `inet_addr()`, `inet_ntoa()`: convierte dirección IP en `char` a `struct in_addr` y viceversa. No admiten IPv6.
  - `send()`: envía datos a través de un TCP socket. Para un chat habrá que determinar cuando empieza y termina un mensaje en el working buffer de `recv()`, por los posibles envíos parciales de información -> estructura de paquete con (longitud, usuario, mensaje) o similar, según sea RFC, para llamar a `recv()` hasta que los bytes recibidos sean igual al que pone en longitud. El working buffer debe tener el tamaño de 2 paquetes al menos porque podemos enviar la parte final de uno y el comienzo del siguiente antes de operar con el primero.
  - `recv()`: lee datos entrantes del remoto al buffer. Devuelve los bytes recibidos. Si el remoto ha cerrado la conexión, devuelve 0.
  - `fcntl(socket_fd, F_SETFL, O_NONBLOCK)`: hace al socket descriptor non-blocking.
  - `select()`, `poll()`, `kqueue()`, `epoll()`: forma de que un solo thread trabaje con varios socket descriptors. Gives you the power to monitor several sockets at the same time. It’ll tell you which ones are ready for reading, which are ready for writing, and which sockets have raised exceptions.
  - `FD_CLR`: removes a particular fd from the set.
  - `FD_COPY`: reemplaza un fd set por otro.
  - `FD_ISSET`: returns true if fd is in the set.
  - `FD_SET`: adds fd to the set.
  - `FD_ZERO`: clears all entries from the set.
  - `signal`
  - `lseek`
  - `fstat`
</details>

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- GETTING STARTED -->
## 🏃 Quick Start

### Important

* Project has only been tested and runned on macOS systems

### Installation

* Clone the repo
  ```sh
  git clone https://github.com/its-a-maxi/ft_irc.git
  ```
  
<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## ⌨️ Usage

* Compile
```sh
  make
```
* Run
``` sh
  ./ircserv [host:port_network:password_network] <port> <password>
```

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- CONTACT -->
## 📫 Contact

Maximo Monroy - monroy.vds@gmail.com

Alejandro León - https://github.com/ElHuaco

Fernando Jimenez - https://github.com/fjimenez81

Project Link: [https://github.com/its-a-maxi/ft_irc](https://github.com/its-a-maxi/ft_irc)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## 🥇 Acknowledgments

* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html//index.html#what-is-a-socket)
* [Building an IRC Server for Vim in C](https://www.youtube.com/watch?v=Cct_vXCJOFw)
* [Introduction to TCP/IP and Sockets, part 1: Introducing the protocols and API](https://www.youtube.com/watch?v=C7CpfL1p6y0)
* [Introduction to TCP/IP and Sockets, part 2: Example code Walk-Through](https://www.youtube.com/watch?v=OuYPe_HcLWc)
* [A typical client-server program flow chart](https://www.ibm.com/docs/en/zos/2.4.0?topic=internets-typical-client-server-program-flow-chart#o4ag1__tiptcp)
* [IRC Ports](https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml?search=IRC)


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
