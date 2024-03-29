## 1. 套接字在网络编程中的作用是什么？为何称它是套接字？

套接字（Socket）在网络编程中起到一个连接节点的作用，它是客户端与服务器端通信的一个端点。就像电脑插座为了链接电源一样，套接字就像一个“通信插座”，在网络传输中负责连接服务器和客户端进行数据交换。

我们将其称为套接字的原因是，这个词来源于英文"Socket"，字面意思是“插座”或“插口”。在计算机网络中，可以类比为数据交换的插口，是网络通信过程的端点。就像插座可以连接电器和电源，这里的插座（套接字）则是连接应用程序与网络协议的。所以我们称这种通信端点为套接字。

## 2. 在服务器端创建套接字后，会依次调用 listen 函数和 accept 函数，比较说明两者作用

在服务器端创建套接字后，listen 函数和 accept 函数有不同的作用。它们通常在服务器端开启服务后被连续使用。

listen 函数的作用是将一个未连接的套接字转换为一个被动套接字，指示内核应接受指向此套接字的连接请求。其中的参数通常被定义为最大连接请求队列的长度。一旦服务器端的套接字进入 listen 状态，就表明它已经做好准备接收客户发来的连接请求。但是，listen 函数并不会建立连接，它只是为一个到达的连接请求设置一个队列。

当有新的客户端请求连接时，服务器端可以通过调用 accept 函数来接受这个请求，并建立一个新的套接字来实现和特定客户端的网络通信。可以说，accept 函数是创建一个新的通信连接。

所以，简单来说，listen 函数用于开启服务器端的监听状态，等待客户端的连接请求；而 accept 函数则是真正建立起服务器和客户端之间的网络连接。

## 3. Linux 中，对套接字数据进行 I/O 时候，可以直接使用文件 I/O 相关函数，而在 Windows 中不可以，原因是什么？

在 Linux 系统中，所有的设备，包括套接字(socket)都被当作文件处理。这也就是常说的“一切皆文件”原则。在这种设计之下，文件 I/O 的读写函数（如read()，write() 等）都可以使用在文件描述符上，而套接字在 Linux 下也被当作一种特殊的文件描述符，所以可以直接使用文件 I/O 的相关函数进行读写操作。

然而，在 Windows 系统中，这样的设计原则并不存在。文件和套接字被区别对待，虽然它们都使用句柄(handle)来处理，但是并不通用。因此，Windows 上的套接字不能直接使用文件 I/O 相关函数，反而需要使用专门为网络设计的函数比如：send()，recv() 等等来进行操作。

这就是为什么在 Linux 中你可以直接对套接字使用文件 I/O 函数进行数据操作，而在 Windows 系统中则不行。由于不同的系统设计理念导致了这样的差别。

## 4. 创建套接字后一般会给它分配地址，为什么？为了完成地址分配需要调用哪个函数？

给套接字分配地址，是因为在网络通信中，要让其他设备找到并连接自己，必须有一个明确的地址。这个地址通常包括 IP 地址和端口号。IP 地址定位网络上的主机，而端口号则定位主机上运行的特定进程或应用程序。

地址分配主要是通过调用 bind() 函数完成的。bind 函数将一个本地地址（IP 地址和端口号）分配给一个套接字。当一个套接字首次被创建时，它既没有名字也没有地址。如果想要其他计算机或者在同一计算机上的其他进程找到这个套接字，就必须给它指定一个地址。因此，bind 函数通常在 listen 函数之前调用，以便在服务器开始监听客户端连接请求之前，就已经给套接字绑定了一个明确的地址。

## 5. Linux 文件描述符与 Windows 的句柄实际上非常类似，请以套接字对象说明它们的含义？

在 Linux 系统中，文件描述符是一个用于访问文件或 IO 资源的整型的标识符。由于 Linux 系统遵循“一切皆文件”的设计理念，因此包括设备、管道、套接字等在内的几乎所有的 IO 操作都可以使用文件描述符来表示。在网络编程中，当我们创建套接字时，系统会返回一个整数，我们把这个整数称之为套接字描述符，用以识别这个套接字。

而在 Windows 系统中，句柄是一个代表资源的引用。句柄系统是 Windows 内核提供的，用于访问和管理系统资源，比如文件、线程、进程、设备上下文、定时器、套接字等。每个句柄都是唯一的，它代表正在被当前进程使用的一个资源。对于套接字来说，Windows 系统通过返回一个套接字句柄，来表示和标识这个特定的套接字。

总体来说，无论是 Linux 的文件描述符还是 Windows 的句柄，都是代表特定资源（在这里是套接字）的标识符，只不过由于操作系统内部设计和管理资源的方式不同，所以它们被赋予了不同的名称。

## 6. 底层文件 I/O 函数与 ANSI 标准定义的文件 I/O 函数之间有何区别？

ANSI 标准定义的文件 I/O 函数，又称为标准 I/O（stdio），例如 fopen，fread，fwrite，fclose 等。

这套函数库提供了结构化和缓存的文件I/O操作，易读性强，易于编程，同时具有一定的跨平台特性。但是它是将一些操作细节封装在库中，实际的执行效率可能不如直接调用底层的 I/O 函数。


底层文件 I/O 函数，又称为不带缓冲的 I/O，如 open, read, write, close 等，

这些都是直接对操作系统系统调用进行封装，能够更加灵活地控制一些底层的特性，比如指定打开模式，文件权限等。而且它们运行效率较高，不需要经历将数据复制到用户空间的缓冲区等额外操作，但是编程可能会相对复杂一些。

所以，选择 ANSI 标准 I/O 函数还是底层 I/O 函数，主要取决于需要考虑的问题：是否需要跨平台，是否需要直接控制底层细节，效率高优先还是易用性高优先等。


## 7.参考本书的示例 `low_open.c low_read.c`, 分别利用底层文件 I/O 和ANSI 标准 I/O 编写文件复制程序，可以任意指定复制程序的使用方法。
