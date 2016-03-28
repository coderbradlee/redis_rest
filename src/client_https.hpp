#ifndef CLIENT_HTTPS_HPP
#define	CLIENT_HTTPS_HPP

#include "client_http.hpp"
#include <boost/asio/ssl.hpp>

namespace SimpleWeb 
{
    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> HTTPS;
    
    template<>
    class Client<HTTPS> : public ClientBase<HTTPS> 
	{
    public:
        Client(const std::string& server_port_path, bool verify_certificate=true, 
                const std::string& cert_file=std::string(), const std::string& private_key_file=std::string(), 
                const std::string& verify_file=std::string()) : 
                ClientBase<HTTPS>::ClientBase(server_port_path, 443), asio_context(boost::asio::ssl::context::sslv23) 
		{
            if(verify_certificate)
                asio_context.set_verify_mode(boost::asio::ssl::verify_peer);
            else
                asio_context.set_verify_mode(boost::asio::ssl::verify_none);
            
            if(cert_file.size()>0 && private_key_file.size()>0) 
			{
				//cout << __LINE__ << endl;
                asio_context.use_certificate_chain_file(cert_file);
				//cout << __LINE__ << endl;
                asio_context.use_private_key_file(private_key_file, boost::asio::ssl::context::pem);
            }
            // cout << __LINE__ << endl;
            if(verify_file.size()>0)
                asio_context.load_verify_file(verify_file);
            //cout << __LINE__ << endl;
            socket=std::make_shared<HTTPS>(asio_io_service, asio_context);
        };

    private:
        boost::asio::ssl::context asio_context;
		boost::system::error_code  ec;
        void connect() 
		{
            if(socket_error || !socket->lowest_layer().is_open()) 
			{
                boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
                boost::asio::connect(socket->lowest_layer(), asio_resolver.resolve(query));
                
                boost::asio::ip::tcp::no_delay option(true);
                socket->lowest_layer().set_option(option);
				cout << __LINE__ <<":"<<host<<" "<<port<< endl;
                socket->handshake(boost::asio::ssl::stream_base::client,ec);
               
                socket_error=false;
				if (ec)
				{
					std::cout << "handshake done, ec=" << ec.message() << std::endl;
				}
				/*boost::asio::ip::tcp::resolver resolver(asio_io_service);
				boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
				boost::asio::async_connect(socket->lowest_layer(), iterator,boost::bind(&Client::handle_connect, this,boost::asio::placeholders::error));*/
				//boost::asio::async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port), boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error));
            }
        }
		void handle_connect(const boost::system::error_code& error)
		{
			if (!error)
			{
				cout << __LINE__ << endl;
				socket->async_handshake(boost::asio::ssl::stream_base::client,boost::bind(&Client::handle_handshake, this,boost::asio::placeholders::error));
				//socket->async_handshake(boost::asio::ssl::stream_base::client, boost::bind(nullptr, this, boost::asio::placeholders::error));
			}
			else
			{
				std::cout << "Connect failed: " << error.message() << "\n";
			}
		}

		void handle_handshake(const boost::system::error_code& error)
		{
			if (!error)
			{
				std::cout << "Enter message: ";
				/*std::cin.getline(request_, max_length);
				size_t request_length = strlen(request_);*/

				//boost::asio::async_write(*socket,boost::asio::buffer(request_, request_length),boost::bind(&client::handle_write, this,boost::asio::placeholders::error,		boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				std::cout << "Handshake failed: " << error.message() << "\n";
			}
		}
/*
		void handle_write(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				boost::asio::async_read(socket_,
					boost::asio::buffer(reply_, bytes_transferred),
					boost::bind(&client::handle_read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				std::cout << "Write failed: " << error.message() << "\n";
			}
		}

		void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				std::cout << "Reply: ";
				std::cout.write(reply_, bytes_transferred);
				std::cout << "\n";
			}
			else
			{
				std::cout << "Read failed: " << error.message() << "\n";
			}
		}*/
    };
}

#endif	/* CLIENT_HTTPS_HPP */