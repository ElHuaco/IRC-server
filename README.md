# ft_irc
 The goal of this project is to make you write your own IRC server. To do so, you will follow the real IRC RFC and test your work with real IRC clients. Internet is ruled by solid and standards protocols that allow a strong interaction between every connected computer. It’s always good to know about it.
 
 Steps
 -------------
   1. [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html//index.html)
   2. [Beej's cheesy chat example](https://beej.us/guide/bgnet/examples/selectserver.c)
   3. [RFC for Human beings](https://modern.ircdocs.horse/)
   4. ????
   5. Profit

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
  - [X] [Biblia introductora a programación de redes](https://beej.us/guide/bgnet/html//index.html#what-is-a-socket)
  - [Loco crea IRC server en C para NeoVim](https://www.youtube.com/watch?v=Cct_vXCJOFw)
  - [X] [Tutorial Parte 1](https://www.youtube.com/watch?v=C7CpfL1p6y0): repaso IP, TCP, sockets.
  - [X] [Tutorial Parte 2](https://www.youtube.com/watch?v=OuYPe_HcLWc): abstraer el código de conexión con Socket, Server classes.
  - [Esquema aplicación server-client socket](https://www.ibm.com/docs/en/zos/2.4.0?topic=internets-typical-client-server-program-flow-chart#o4ag1__tiptcp)
  - [Puertos IRC](https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml?search=IRC)

¿Qué es el RFC?
---------------

Request For Comments, son la documentación del IRC.
  - [X] [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459)
  - [ ] [RFC 2810](https://datatracker.ietf.org/doc/html/rfc2810)
  - [ ] [RFC 2811](https://datatracker.ietf.org/doc/html/rfc2811)
  - [ ] [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)
  - [ ] [RFC 2813](https://datatracker.ietf.org/doc/html/rfc2813)
  - [ ] [RFC 7194](https://datatracker.ietf.org/doc/html/rfc7194)

Mandatory parts
---------------

  - ./ircserv [host:port_network:password_network] \<port\> \<password\>
  - Varios clientes a la vez sin colgarse.
  - No forking, all I/O non-blocking and use only 1 select for all T/O operations (read, write, listen...)
    - ¿Qué significan non-blocking sockets? Any descriptor (pipes, FIFOs, sockets, terminals, pseudo-terminals, and some other types of devices) can be put in the nonblocking mode. When a descriptor is set in nonblocking mode, an I/O system call on that descriptor will return immediately, even if that request can’t be immediately completed (and would therefore result in the process being blocked otherwise). 
      - TCP/IP Socket: Once a peer-to-peer connection is established, a socket descriptor is used to uniquely identify the connection. The socket descriptor itself is a task-specific numerical value.
  - Verificar errores en low bandwith, partial data received...
  - test con nc para enviar cachos de un command.
  - Lista mínimos del RFC:
    - You must be able to connect the reference client to your server without producing any error.
    - You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using this client.
    - All messages from one client on a channel are sent to all other clients of the channel.
    - You must have operators and regular users. Some operator’s specific actions/commands.

  
Funciones Externas
-------------------

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
  - signal
  - lseek
  - fstat
