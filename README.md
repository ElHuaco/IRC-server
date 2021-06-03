# ft_irc
 The goal of this project is to make you write your own IRC server. To do so, you will follow the real IRC RFC and test your work with real IRC clients. Internet is ruled by solid and standards protocols that allow a strong interaction between every connected computer. It’s always good to know about it.

¿Qué es el IRC?
---------------

[IRC:](https://es.wikipedia.org/wiki/Internet_Relay_Chat) es un "application layer" sobre la Internet, que permite comunicación por
texto. Este chat funciona con un modelo de red "cliente/servidor".
  - [Internet](https://developer.mozilla.org/en-US/docs/Learn/Common_questions/How_does_the_Internet_work)
  - Application Layer: es un "abstraction layer" que especifica los protocolos de comunicación compartidos por los "hosts de la red", así como los métodos de interfaz usados.
    - Abstraction Layer: categorización de los entresijos de un sistema para poder atacarlos por separado.
    - Host de Red: ordenador conectado a una red, asignado con una dirección red al menos.
  - Modelo Cliente/Servidor: es una forma de "distributed application" donde se reparten las tareas entre los proveedores de un servicio (servidores) y los usuarios del servicio (clientes). Un "host de red" del servicio ejecuta programas que pueden compartir sus recursos con lo clientes. Un cliente no comparte sus recursos, pero sí que exige el servicio al servidor.
    - Distributed Application: programa que se ejecuta en un "distributed system".
      - Distributed System: sistema cuyas componentes están en diferentes ordenadores de la red, como los MMORPGs.
Los clientes IRC se comunican con los servidores del chat para transmitir mensajes a otros clientes. Debe ser TCP/IP(v4) ó (v6).
  - [TCP/IP](https://www.youtube.com/watch?v=614QGgw_FA4)

Ejemplos de lunáticos creando servidores TCP/IP socket en C/C++
---------------
  - [ ] [Programación básica de redes](https://beej.us/guide/bgnet/html//index.html#what-is-a-socket)
  - [Loco crea IRC server en C para NeoVim](https://www.youtube.com/watch?v=Cct_vXCJOFw)
  - [X] [Tutorial Parte 1](https://www.youtube.com/watch?v=C7CpfL1p6y0): repaso IP, TCP, sockets.
  - [X] [Tutorial Parte 2](https://www.youtube.com/watch?v=OuYPe_HcLWc): abstraer el código de conexión con Socket, Server classes.
  - [Esquema aplicación server-client socket](https://www.ibm.com/docs/en/zos/2.4.0?topic=internets-typical-client-server-program-flow-chart#o4ag1__tiptcp)
  - [Puertos IRC](https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml?search=IRC)

¿Qué es el RFC?
---------------

Request For Comments, son la documentación del IRC.
  - [ ] [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459)
  - [ ] [RFC 2810](https://datatracker.ietf.org/doc/html/rfc2810)
  - [ ] [RFC 2811](https://datatracker.ietf.org/doc/html/rfc2811)
  - [ ] [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)
  - [ ] [RFC 2813](https://datatracker.ietf.org/doc/html/rfc2813)
  - [ ] [RFC 7194](https://datatracker.ietf.org/doc/html/rfc7194)

Mandatory parts
---------------

  - Server-Server comunication, con servidores reales
  - Use cryptographic library to handle TLS communications
  - ./ircserv [host:port_network:password_network] <port> <password>
  - Varios clientes, servidores a la vez sin colgarse.
  - No forking, all IO non-blocking and use only 1 select for all (read, write, listen...)
    - ¿Qué significan non-blocking sockets? Any descriptor (pipes, FIFOs, sockets, terminals, pseudo-terminals, and some other types of devices) can be put in the nonblocking mode. When a descriptor is set in nonblocking mode, an I/O system call on that descriptor will return immediately, even if that request can’t be immediately completed (and would therefore result in the process being blocked otherwise). 
      - TCP/IP Socket: Once a peer-to-peer connection is established, a socket descriptor is used to uniquely identify the connection. The socket descriptor itself is a task-specific numerical value.
  - Verificar errores en low bandwith, partial data received...
  - test con nc para enviar cachos de un command.
  
Funciones Externas
-------------------

  - `socket()`: lo crea. Selecciona protocolos (`PF_INET` ó `PF_INET6`; `SOCK_STREAM`; `getprotobyname("tcp")`). También se puede rellenar con el `struct addrinfo` usado en `getaddrinfo()`.
  - open: 
  - close
  - setsockopt
  - getsockname
  - getprotobyname
  - gethostbyname
  - getaddrinfo
  - bind
  - connect
  - listen
  - accept
  - htons
  - htonl
  - ntohs
  - ntohl
  - inet_addr
  - inet_ntoa
  - send
  - recv
  - exit
  - signal
  - lseek
  - fstat
  - read
  - write
  - `fcntl(socket_fd, F_SETFL, O_NONBLOCK)`;
  - `select`:  gives you the power to monitor several sockets at the same time. It’ll tell you which ones are ready for reading, which are ready for writing, and which sockets have raised exceptions.
  - `FD_CLR`: removes a particular fd from the set.
  - `FD_COPY`: 
  - `FD_ISSET`: returns true if fd is in the set.
  - `FD_SET`: adds fd to the set.
  - `FD_ZERO`: clears all entries from the set.
