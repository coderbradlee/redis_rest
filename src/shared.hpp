#ifndef SHARED_HPP
#define	SHARED_HPP

#include <boost/asio.hpp>
#include <unordered_map>
#include <map>
#include <random>
#include <memory>
namespace SimpleWeb
{

	bool Base64Encode(const string& input, string* output)
	{
		typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<string::const_iterator, 6, 8> > Base64EncodeIterator;
		stringstream result;
		copy(Base64EncodeIterator(input.begin()), Base64EncodeIterator(input.end()), ostream_iterator<char>(result));
		size_t equal_count = (3 - input.length() % 3) % 3;
		for (size_t i = 0; i < equal_count; i++) {
			result.put('=');
		}
		*output = result.str();
		return output->empty() == false;
	}

	bool Base64Decode(const string& input, string* output)
	{
		typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<string::const_iterator>, 8, 6> Base64DecodeIterator;
		stringstream result;
		try {
			copy(Base64DecodeIterator(input.begin()), Base64DecodeIterator(input.end()), ostream_iterator<char>(result));
		}
		catch (...) {
			return false;
		}
		*output = result.str();
		return output->empty() == false;
	}


	std::string&   replace_all(std::string&   str, const   std::string&   old_value, const   std::string&   new_value)
	{
		while (true)   {
			std::string::size_type   pos(0);
			if ((pos = str.find(old_value)) != std::string::npos)
				str.replace(pos, old_value.length(), new_value);
			else   break;
		}
		return   str;
	}
	std::string&   replace_all_distinct(std::string&   str, const   std::string&   old_value, const   std::string&   new_value)
	{
		for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())   {
			if ((pos = str.find(old_value, pos)) != std::string::npos)
				str.replace(pos, old_value.length(), new_value);
			else   break;
		}
		return   str;
	}
}
#endif	/* CLIENT_HTTP_HPP */