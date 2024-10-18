#ifndef _ULIF_
#define _ULIF_

#include "pxm_primitives.hpp"

#include <fstream>
#include <string>

namespace dt0
{	
	struct pxm_info
	{
		void* image_matrix{};
		uint32_t height_pixels{ 0 };
		uint32_t width_pixels{ 0 };
		uint16_t pixel_channels{ 0 };
		uint16_t pixel_channel_size_bits{ 0 };
	};

	class pxm_base
	{
	public:
		virtual void load(std::string file_path) = 0;
		virtual void write(std::string file_path, pxm_info& write_info) = 0;
		virtual void save(std::string file_path) = 0;
		virtual ___nodiscard___ void* image_matrix() const = 0;
		virtual ___nodiscard___ uint64_t file_size_bytes() const = 0;
		virtual ___nodiscard___ uint64_t data_size_bytes() const = 0;
		virtual ___nodiscard___ uint32_t height_pixels() const = 0;
		virtual ___nodiscard___ uint32_t width_pixels() const = 0;
		virtual ___nodiscard___ uint16_t pixel_channels() const = 0;
		virtual ___nodiscard___ uint16_t pixel_size_bits() const = 0;
		virtual ___nodiscard___ uint16_t pixel_channel_size_bits() const = 0;
	};

	template <typename _pxmfmt_t, typename _pxmpc_t>
	class pxm final : public pxm_base
	{
	public:
		static_assert(is_valid_pxm_pixel_format_type<_pxmfmt_t>::value, "Invalid pxm pixel format type!");
		static_assert(is_valid_pxm_pixel_channel_type<_pxmpc_t>::value, "Invalid pxm pixel channel type!");

		typedef _pxmfmt_t pxm_pixel_format_type;
		typedef _pxmpc_t  pxm_pixel_channel_type;
		typedef pxm_pixel<_pxmfmt_t, _pxmpc_t> pixel_type;

	public:
		pxm() noexcept = default;

		pxm(std::string file_path)
		{
			if (file_path.substr(file_path.find_last_of('.'), std::string::npos) != std::string(_pxm_extension))
				throw std::exception("Unsupported file extension!");

			try
			{
				this->_read(file_path.c_str());
			}

			catch (std::exception exc)
			{
				throw;
			}
		}

		pxm(const pxm& other)
		{
			if (this == __builtin_addressof(other))
				throw std::exception("Self-assignment is not allowed!");

			_image_matrix = *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(other.image_matrix()));

			_file_size_bytes = other.file_size_bytes();
			_data_size_bytes = other.data_size_bytes();

			_height_pixels = other.height_pixels();
			_width_pixels = other.width_pixels();
			_pixel_channels = other.pixel_channels();
			_pixel_size_bits = other.pixel_size_bits();
			_pixel_channel_size_bits = other.pixel_channel_size_bits();
		}

		pxm(pxm&& other) noexcept
		{
			if (*this == other)
				throw std::exception("Self-assignment is not allowed!");

			_image_matrix = *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(other.image_matrix()));

			_file_size_bytes = std::move(other.file_size_bytes());
			_data_size_bytes = std::move(other.data_size_bytes());

			_height_pixels = std::move(other.height_pixels());
			_width_pixels = std::move(other.width_pixels());
			_pixel_channels = std::move(other.pixel_channels());
			_pixel_size_bits = std::move(other.pixel_size_bits());
			_pixel_channel_size_bits = std::move(other.pixel_channel_size_bits());
		}

		const pxm& operator=(const pxm& other)
		{
			if (this == __builtin_addressof(other))
				return *this;
	
			_image_matrix = *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(other.image_matrix()));

			_file_size_bytes = other.file_size_bytes();
			_data_size_bytes = other.data_size_bytes();

			_height_pixels = other.height_pixels();
			_width_pixels = other.width_pixels();
			_pixel_channels = other.pixel_channels();
			_pixel_size_bits = other.pixel_size_bits();
			_pixel_channel_size_bits = other.pixel_channel_size_bits();

			return *this;
		}

		const pxm& operator=(pxm&& other) noexcept
		{
			if (*this == other)
				return *this;

			_image_matrix = *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(other.image_matrix()));

			_file_size_bytes = std::move(other.file_size_bytes());
			_data_size_bytes = std::move(other.data_size_bytes());

			_height_pixels = std::move(other.height_pixels());
			_width_pixels = std::move(other.width_pixels());
			_pixel_channels = std::move(other.pixel_channels());
			_pixel_size_bits = std::move(other.pixel_size_bits());
			_pixel_channel_size_bits = std::move(other.pixel_channel_size_bits());

			return *this;
		}

		~pxm() noexcept = default;

		void load(std::string file_path) override
		{
			if (file_path.substr(file_path.find_last_of('.'), std::string::npos) != std::string(_pxm_extension))
				throw std::exception("Unsupported file extension!");

			if (!_empty())
				_reset();

			try
			{
				this->_read(file_path.c_str());
			}

			catch (std::exception exc)
			{
				throw;
			}
		}

		void write(std::string file_path, pxm_info& write_info) override
		{
			if (file_path.substr(file_path.find_last_of('.'), std::string::npos) != std::string(_pxm_extension))
				throw std::exception("Unsupported file extension!");

			_image_matrix = *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(write_info.image_matrix));

			_height_pixels = write_info.height_pixels;
			_width_pixels = write_info.width_pixels;
			_pixel_channels = write_info.pixel_channels;
			_pixel_channel_size_bits = write_info.pixel_channel_size_bits;

			_pixel_size_bits = (_pixel_channels * _pixel_channel_size_bits);

			_data_size_bytes = ((static_cast<uint64_t>(_height_pixels) * static_cast<uint64_t>(_width_pixels)) * (sizeof(pxm_pixel_channel_type) * _pixel_channels));
			_file_size_bytes = (_data_size_bytes + _header_size_bytes);

			try
			{
				this->_write(file_path.c_str());
			}

			catch (std::exception exc)
			{
				throw;
			}
		}

		void save(std::string file_path) override
		{
			if (file_path.substr(file_path.find_last_of('.'), std::string::npos) != std::string(_pxm_extension))
				throw std::exception("Unsupported file extension!");

			if (_image_matrix.empty())
				throw std::exception("No writeable data available!");

			try
			{
				this->_write(file_path.c_str());
			}

			catch (std::exception exc)
			{
				throw;
			}
		}

		___nodiscard___  void* image_matrix() const override
		{
			return reinterpret_cast<void*>(&_image_matrix);
		}

		___nodiscard___ uint64_t file_size_bytes() const override
		{
			return _file_size_bytes;
		}

		___nodiscard___ uint64_t data_size_bytes() const override
		{
			return _data_size_bytes;
		}

		___nodiscard___ uint32_t height_pixels() const override
		{
			return _height_pixels;
		}

		___nodiscard___ uint32_t width_pixels() const override
		{
			return _width_pixels;
		}

		___nodiscard___ uint16_t pixel_channels() const override
		{
			return _pixel_channels;
		}

		___nodiscard___ uint16_t pixel_size_bits() const override
		{
			return _pixel_size_bits;
		}

		___nodiscard___ uint16_t pixel_channel_size_bits() const override
		{
			return _pixel_channel_size_bits;
		}

		___nodiscard___ bool operator==(const pxm& other) const
		{
			return (_image_matrix == *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(other.image_matrix())));
		}

		___nodiscard___ bool operator!=(const pxm& other) const
		{
			return (_image_matrix != *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(other.image_matrix())));
		}

	private:
		void _read(const char* file_path)
		{
			std::ifstream input(file_path, std::ios::binary);

			if (!input.is_open())
				throw std::exception("File couldn't be/wasn't opened properly!");

			long offset = 0;

			char* chunk_IDs_reader = new char[_chunk_IDs_size];

			input.read(chunk_IDs_reader, _chunk_IDs_size);

			for (uint16_t i = 0; i < _chunk_IDs_size; ++i)
			{
				if (chunk_IDs_reader[i] != _head_chunk_ID[i])
				{
					delete[] chunk_IDs_reader;
					input.close();

					throw std::exception("Invalid head chunk ID read from file!");
				}
			}

			offset += _chunk_IDs_size;
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_file_size_bytes), sizeof(uint64_t));

			offset += sizeof(uint64_t);
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_data_size_bytes), sizeof(uint64_t));

			offset += sizeof(uint64_t);
			input.seekg(offset, input.beg);

			input.read(chunk_IDs_reader, _chunk_IDs_size);

			for (uint16_t i = 0; i < _chunk_IDs_size; ++i)
			{
				if (chunk_IDs_reader[i] != _info_chunk_ID[i])
				{
					delete[] chunk_IDs_reader;
					input.close();

					throw std::exception("Invalid info chunk ID read from file!");
				}
			}

			offset += _chunk_IDs_size;
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_height_pixels), sizeof(uint32_t));

			offset += sizeof(uint32_t);
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_width_pixels), sizeof(uint32_t));

			offset += sizeof(uint32_t);
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_pixel_channels), sizeof(uint16_t));

			if ((_pixel_channels != pxmrgb::channels) && (_pixel_channels != pxmrgba::channels))
			{
				delete[] chunk_IDs_reader;
				input.close();

				throw std::exception("Invalid pixel channel count read from file!");
			}

			offset += sizeof(uint16_t);
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_pixel_size_bits), sizeof(uint16_t));

			uint16_t counter;

			for (counter = 0; counter < _valid_pixel_sizes_bits_size; ++counter)
			{
				if (_pixel_size_bits == _valid_pixel_sizes_bits[counter])
				{
					break;
				}
			}

			if (counter == _valid_pixel_sizes_bits_size)
			{
				delete[] chunk_IDs_reader;
				input.close();

				throw std::exception("Invalid pixel size read from file!");
			}

			offset += sizeof(uint16_t);
			input.seekg(offset, input.beg);

			input.read(reinterpret_cast<char*>(&_pixel_channel_size_bits), sizeof(uint16_t));

			for (counter = 0; counter < _valid_pixel_channel_sizes_bits_size; ++counter)
			{
				if (_pixel_channel_size_bits == _valid_pixel_channel_sizes_bits[counter])
				{
					break;
				}
			}

			if (counter == _valid_pixel_channel_sizes_bits_size)
			{
				delete[] chunk_IDs_reader;
				input.close();

				throw std::exception("Invalid pixel channel size read from file!");
			}

			offset += sizeof(uint16_t);
			input.seekg(offset, input.beg);

			input.read(chunk_IDs_reader, _chunk_IDs_size);

			for (uint16_t i = 0; i < _chunk_IDs_size; ++i)
			{
				if (chunk_IDs_reader[i] != _data_chunk_ID[i])
				{
					delete[] chunk_IDs_reader;
					input.close();

					throw std::exception("Invalid data chunk ID read from file!");
				}
			}

			delete[] chunk_IDs_reader;

			offset += _chunk_IDs_size;
			input.seekg(offset, input.beg);

			_image_matrix.new_matrix(_height_pixels, _width_pixels);

			if (sizeof(pxm_pixel_channel_type) == sizeof(uint8_t))
			{
				uint8_t* data_transfer = new uint8_t[_pixel_channels];

				pxm_pixel_channel_type* pixel_transfer = new pxm_pixel_channel_type[_pixel_channels];

				for (uint64_t i = 0; i < _image_matrix.size(); ++i)
				{
					input.read(reinterpret_cast<char*>(data_transfer), (_pixel_channels * sizeof(pxm_pixel_channel_type)));
					offset += (_pixel_channels * sizeof(pxm_pixel_channel_type));
					input.seekg(offset, input.beg);

					for (uint16_t u = 0; u < _pixel_channels; ++u)
						pixel_transfer[u] = data_transfer[u];

					_image_matrix.push(std::move(pixel_type(pixel_transfer, (pixel_transfer + _pixel_channels))));
				}

				delete[] pixel_transfer;

				delete[] data_transfer;
			}

			else
			{
				uint16_t* data_transfer = new uint16_t[_pixel_channels];

				pxm_pixel_channel_type* pixel_transfer = new pxm_pixel_channel_type[_pixel_channels];

				for (uint64_t i = 0; i < _image_matrix.size(); ++i)
				{
					input.read(reinterpret_cast<char*>(data_transfer), (_pixel_channels * sizeof(pxm_pixel_channel_type)));
					offset += (_pixel_channels * sizeof(pxm_pixel_channel_type));
					input.seekg(offset, input.beg);

					for (uint16_t u = 0; u < _pixel_channels; ++u)
						pixel_transfer[u] = data_transfer[u];

					_image_matrix.push(std::move(pixel_type(pixel_transfer, (pixel_transfer + _pixel_channels))));
				}

				delete[] pixel_transfer;

				delete[] data_transfer;
			}

			input.close();
		}

		void _write(const char* file_path) 
		{
			std::ofstream output(file_path, std::ios::binary);

			if (!output.is_open())
				throw std::exception("File couldn't be/wasn't opened properly!");

			output.write(_head_chunk_ID, _chunk_IDs_size);
			
			output.write(reinterpret_cast<const char*>(&_file_size_bytes), sizeof(uint64_t));
			output.write(reinterpret_cast<const char*>(&_data_size_bytes), sizeof(uint64_t));

			output.write(_info_chunk_ID, _chunk_IDs_size);

			output.write(reinterpret_cast<const char*>(&_height_pixels), sizeof(uint32_t));
			output.write(reinterpret_cast<const char*>(&_width_pixels), sizeof(uint32_t));
			output.write(reinterpret_cast<const char*>(&_pixel_channels), sizeof(uint16_t));
			output.write(reinterpret_cast<const char*>(&_pixel_size_bits), sizeof(uint16_t));
			output.write(reinterpret_cast<const char*>(&_pixel_channel_size_bits), sizeof(uint16_t));

			output.write(_data_chunk_ID, _chunk_IDs_size);

			if (sizeof(pxm_pixel_channel_type) == sizeof(uint8_t))
			{
				uint8_t* data_transfer = new uint8_t[_pixel_channels];
				
				pxm_pixel_channel_type* pixel_transfer = nullptr;

				for (uint64_t i = 0; i < _image_matrix.size(); ++i)
				{
					pixel_transfer = _image_matrix[i].data();

					for (uint16_t c = 0; c < _pixel_channels; ++c)
					{
						data_transfer[c] = pixel_transfer[c].value();
					}

					output.write(reinterpret_cast<const char*>(data_transfer), (_pixel_channels * sizeof(pxm_pixel_channel_type)));
				}

				delete[] data_transfer;
			}

			else
			{
				uint16_t* data_transfer = new uint16_t[_pixel_channels];

				pxm_pixel_channel_type* pixel_transfer = nullptr;

				for (uint64_t i = 0; i < _image_matrix.size(); ++i)
				{
					pixel_transfer = _image_matrix[i].data();

					for (uint16_t c = 0; c < _pixel_channels; ++c)
					{
						data_transfer[c] = pixel_transfer[c].value();
					}

					output.write(reinterpret_cast<const char*>(data_transfer), (_pixel_channels * sizeof(pxm_pixel_channel_type)));
				}

				delete[] data_transfer;
			}

			output.close();
		}

		___nodiscard___ bool _empty() const
		{
			return ((_image_matrix.empty()) && (_file_size_bytes == 0) && (_data_size_bytes == 0) &&
					(_height_pixels == 0) && (_width_pixels == 0) && (_pixel_channels == 0) &&
					(_pixel_size_bits == 0) && (_pixel_channel_size_bits == 0));
		}

		void _reset() 
		{
			_image_matrix.clear();

			_file_size_bytes = 0;
			_data_size_bytes = 0;

			_height_pixels = 0;
			_width_pixels = 0;
			_pixel_channels = 0;
			_pixel_size_bits = 0;
			_pixel_channel_size_bits = 0;
		}

	private:
		/* Head chunk */
		const char _head_chunk_ID[5] = "PXM ";
		uint64_t _file_size_bytes = 0;
		uint64_t _data_size_bytes = 0;

		/* Info chunk */
		const char _info_chunk_ID[5] = "INFO";
		uint32_t _height_pixels = 0;
		uint32_t _width_pixels = 0;
		uint16_t _pixel_channels = 0;
		uint16_t _pixel_size_bits = 0;
		uint16_t _pixel_channel_size_bits = 0;

		/* Data chunk */
		const char _data_chunk_ID[5] = "DATA";
		mutable pxm_matrix<_pxmfmt_t, _pxmpc_t> _image_matrix;

		const uint16_t _chunk_IDs_size = sizeof(char[4]);

		const uint16_t _header_size_bytes = ((3 * sizeof(const char[4])) + (3 * sizeof(uint64_t)) + (3 * sizeof(uint16_t)));

		const char _pxm_extension[5] = ".pxm";

		/* Checkers */
		const uint16_t _valid_pixel_sizes_bits[9] = { 24, 32, 30, 40, 36, 48, 42, 56, 64 };
		const uint16_t _valid_pixel_sizes_bits_size = 9;

		const uint16_t _valid_pixel_channel_sizes_bits[5] = { 8, 10, 12, 14, 16 };
		const uint16_t _valid_pixel_channel_sizes_bits_size = 5;
	};

	___nodiscard___ pxm_base* get_pxm_container(std::string file_path)
	{
		if (file_path.substr(file_path.find_last_of('.'), std::string::npos) != std::string(".pxm"))
			throw std::exception("Unsupported file extension!");

		std::ifstream input(file_path.c_str(), std::ios::binary);

		if (!input.is_open())
			throw std::exception("File couldn't be/wasn't opened properly!");

		long offset = ((2 * sizeof(char[4])) + (3 * sizeof(uint64_t)));

		input.seekg(offset, input.beg);

		uint16_t number_of_channels = 0;

		input.read(reinterpret_cast<char*>(&number_of_channels), sizeof(uint16_t));

		offset += sizeof(uint32_t);
		input.seekg(offset, input.beg);

		uint16_t pixel_channel_size_bits = 0;

		input.read(reinterpret_cast<char*>(&pixel_channel_size_bits), sizeof(uint16_t));

		input.close();

		pxm_base* output = nullptr;

		if (number_of_channels == pxmrgb::channels)
		{
			switch (pixel_channel_size_bits)
			{
			case 8:
				output = new pxm<pxmrgb, pxmpc8>(file_path);
				break;

			case 10:
				output = new pxm<pxmrgb, pxmpc10>(file_path);
				break;

			case 12:
				output = new pxm<pxmrgb, pxmpc12>(file_path);
				break;

			case 14:
				output = new pxm<pxmrgb, pxmpc14>(file_path);
				break;

			case 16:
				output = new pxm<pxmrgb, pxmpc16>(file_path);
				break;
			}
		}

		else if (number_of_channels == pxmrgba::channels)
		{
			switch (pixel_channel_size_bits)
			{
			case 8:
				output = new pxm<pxmrgba, pxmpc8>(file_path);
				break;

			case 10:
				output = new pxm<pxmrgba, pxmpc10>(file_path);
				break;

			case 12:
				output = new pxm<pxmrgba, pxmpc12>(file_path);
				break;

			case 14:
				output = new pxm<pxmrgba, pxmpc14>(file_path);
				break;

			case 16:
				output = new pxm<pxmrgba, pxmpc16>(file_path);
				break;
			}
		}

		else throw std::exception("Number of channels wasn't read properly!");

		return output;
	}

	class pxm_ptr final
	{
	public:
		pxm_ptr() noexcept = default;

		pxm_ptr(pxm_base* const other) noexcept : _core(other) {}

		pxm_ptr(const pxm_ptr& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("Self-assignment not allowed!");

			_core = other.pointer();
		}

		const pxm_ptr& operator=(pxm_base* const other)
		{
			if (_core == other)
				return *this;

			_core = other;

			return *this;
		}

		const pxm_ptr& operator=(const pxm_ptr& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			_core = other.pointer();

			return *this;
		}

		~pxm_ptr() noexcept
		{
			if (_core != nullptr)
			{
				delete _core;
			}
		}

		___nodiscard___ pxm_base* pointer() const
		{
			return _core;
		}

		pxm_base* const operator->() const
		{
			return _core;
		}

		___nodiscard___ bool operator==(const pxm_ptr& other) const
		{
			return (_core == other.pointer());
		}

		___nodiscard___ bool operator!=(const pxm_ptr& other) const
		{
			return (_core != other.pointer());
		}
		
		___nodiscard___ bool operator==(std::nullptr_t) const
		{
			return (_core == nullptr);
		}

		___nodiscard___ bool operator!=(std::nullptr_t) const
		{
			return (_core != nullptr);
		}

	private:
		pxm_base* _core = nullptr;
	};

	template <typename _pxmfmt_t, typename _pxmpc_t>
	___nodiscard___ inline pxm_matrix<_pxmfmt_t, _pxmpc_t> pxm_matrix_cast(const pxm_ptr& pxm_container_pointer)
	{
		if (!is_valid_pxm_pixel_format_type<_pxmfmt_t>::value)
			throw std::exception("Invalid pxm pixel format type!");

		if (!is_valid_pxm_pixel_channel_type<_pxmpc_t>::value)
			throw std::exception("Invalid pxm pixel channel type!");

		return *(reinterpret_cast<pxm_matrix<_pxmfmt_t, _pxmpc_t>*>(pxm_container_pointer->image_matrix()));
	}
}

#endif /* _ULIF_ */