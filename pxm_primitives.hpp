#ifndef _PXM_PRIMITIVES_
#define _PXM_PRIMITIVES_

#include "core_macros.hpp"

#include <stdint.h>
#include <stdexcept>
#include <utility>
#include <cmath>
#include <initializer_list>
#include <new>
#include <type_traits>
#include <stddef.h>

namespace dt0
{
	class pxmpc8 final
	{
	public:
		pxmpc8() noexcept = default;

		pxmpc8(uint8_t other) noexcept : _core_value(std::move(other)) {}

		pxmpc8(const pxmpc8& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("pxmpc18: Self-assignmet not allowed!");

			_core_value = other.value();
		}

		pxmpc8(pxmpc8&& other) noexcept
		{
			_core_value = std::move(other.value());
		}

		const pxmpc8& operator=(uint8_t other)
		{
			if (_core_value == other)
				return *this;

			_core_value = std::move(other);

			return *this;
		}

		const pxmpc8& operator=(const pxmpc8& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			_core_value = other.value();

			return *this;
		}

		const pxmpc8& operator=(pxmpc8&& other) noexcept
		{
			if (*this == other)
				return *this;

			_core_value = std::move(other.value());

			return *this;
		}

		~pxmpc8() noexcept = default;

		___nodiscard___ uint8_t value() const
		{
			return _core_value;
		}

		___nodiscard___ bool operator==(const pxmpc8& other) const
		{
			return (_core_value == other.value());
		}

		___nodiscard___ bool operator!=(const pxmpc8& other) const
		{
			return (_core_value != other.value());
		}

	private:
		uint8_t _core_value = 0;
	};

	class pxmpc10 final
	{
	public:
		pxmpc10() noexcept
		{
			_core._value = 0;
		}

		pxmpc10(uint16_t other)
		{
			if (other > (std::pow<uint16_t, uint16_t>(2, 10) - 1))
				throw std::overflow_error("pxmpc10: Integer overflow!");

			_core._value = std::move(other);
		}

		pxmpc10(const pxmpc10& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("pxmpc10: Self-assignmet not allowed!");

			_core._value = other.value();
		}

		pxmpc10(pxmpc10&& other) noexcept
		{
			_core._value = std::move(other.value());
		}

		const pxmpc10& operator=(uint16_t other)
		{
			if (_core._value == other)
				return *this;

			if (other > (std::pow<uint16_t, uint16_t>(2, 10) - 1))
				throw std::overflow_error("pxmpc10: Integer overflow!");

			_core._value = std::move(other);

			return *this;
		}

		const pxmpc10& operator=(const pxmpc10& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			_core._value = other.value();

			return *this;
		}

		const pxmpc10& operator=(pxmpc10&& other) noexcept
		{
			if (*this == other)
				return *this;

			_core._value = std::move(other.value());

			return *this;
		}

		~pxmpc10() noexcept = default;

		___nodiscard___ uint16_t value() const
		{
			return _core._value;
		}

		___nodiscard___ bool operator==(const pxmpc10& other) const
		{
			return (_core._value == other.value());
		}

		___nodiscard___ bool operator!=(const pxmpc10& other) const
		{
			return (_core._value != other.value());
		}

	private:
		struct pxmpc10_core
		{
			uint16_t _value : 10;
			uint16_t : 0; // for alignment;
		};

		pxmpc10_core _core;
	};

	class pxmpc12 final
	{
	public:
		pxmpc12() noexcept
		{
			_core._value = 0;
		}

		pxmpc12(uint16_t other)
		{
			if (other > (std::pow<uint16_t, uint16_t>(2, 12) - 1))
				throw std::overflow_error("pxmpc12: Integer overflow!");

			_core._value = std::move(other);
		}

		pxmpc12(const pxmpc12& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("pxmpc12: Self-assignmet not allowed!");

			_core._value = other.value();
		}

		pxmpc12(pxmpc12&& other) noexcept
		{
			_core._value = std::move(other.value());
		}

		const pxmpc12& operator=(uint16_t other)
		{
			if (_core._value == other)
				return *this;

			if (other > (std::pow<uint16_t, uint16_t>(2, 12) - 1))
				throw std::overflow_error("pxmpc12: Integer overflow!");

			_core._value = std::move(other);

			return *this;
		}

		const pxmpc12& operator=(const pxmpc12& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			_core._value = other.value();

			return *this;
		}

		const pxmpc12& operator=(pxmpc12&& other) noexcept
		{
			if (*this == other)
				return *this;

			_core._value = std::move(other.value());

			return *this;
		}

		~pxmpc12() noexcept = default;

		___nodiscard___ uint16_t value() const
		{
			return _core._value;
		}

		___nodiscard___ bool operator==(const pxmpc12& other) const
		{
			return (_core._value == other.value());
		}

		___nodiscard___ bool operator!=(const pxmpc12& other) const
		{
			return (_core._value != other.value());
		}

	private:
		struct pxmpc12_core
		{
			uint16_t _value : 12;
			uint16_t : 0; // for alignment;
		};

		pxmpc12_core _core;
	};

	class pxmpc14 final
	{
	public:
		pxmpc14() noexcept
		{
			_core._value = 0;
		}

		pxmpc14(uint16_t other)
		{
			if (other > (std::pow<uint16_t, uint16_t>(2, 14) - 1))
				throw std::overflow_error("pxmpc14: Integer overflow!");

			_core._value = std::move(other);
		}

		pxmpc14(const pxmpc14& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("pxmpc14: Self-assignmet not allowed!");

			_core._value = other.value();
		}

		pxmpc14(pxmpc14&& other) noexcept
		{
			_core._value = std::move(other.value());
		}

		const pxmpc14& operator=(uint16_t other)
		{
			if (_core._value == other)
				return *this;

			if (other > (std::pow<uint16_t, uint16_t>(2, 14) - 1))
				throw std::overflow_error("pxmpc14: Integer overflow!");

			_core._value = std::move(other);

			return *this;
		}

		const pxmpc14& operator=(const pxmpc14& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			_core._value = other.value();

			return *this;
		}

		const pxmpc14& operator=(pxmpc14&& other) noexcept
		{
			if (*this == other)
				return *this;

			_core._value = std::move(other.value());

			return *this;
		}

		~pxmpc14() noexcept = default;

		___nodiscard___ uint16_t value() const
		{
			return _core._value;
		}

		___nodiscard___ bool operator==(const pxmpc14& other) const
		{
			return (_core._value == other.value());
		}

		___nodiscard___ bool operator!=(const pxmpc14& other) const
		{
			return (_core._value != other.value());
		}

	private:
		struct pxmpc14_core
		{
			uint16_t _value : 14;
			uint16_t : 0; // for alignment;
		};

		pxmpc14_core _core;
	};

	class pxmpc16 final
	{
	public:
		pxmpc16() noexcept = default;

		pxmpc16(uint16_t other) noexcept : _core_value(std::move(other)) {}

		pxmpc16(const pxmpc16& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("pxmpc16: Self-assignmet not allowed!");

			_core_value = other.value();
		}

		pxmpc16(pxmpc16&& other) noexcept
		{
			_core_value = std::move(other.value());
		}

		const pxmpc16& operator=(uint16_t other)
		{
			if (_core_value == other)
				return *this;

			_core_value = std::move(other);

			return *this;
		}

		const pxmpc16& operator=(const pxmpc16& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			_core_value = other.value();

			return *this;
		}

		const pxmpc16& operator=(pxmpc16&& other) noexcept
		{
			if (*this == other)
				return *this;

			_core_value = std::move(other.value());

			return *this;
		}

		~pxmpc16() noexcept = default;

		___nodiscard___ uint16_t value() const
		{
			return _core_value;
		}

		___nodiscard___ bool operator==(const pxmpc16& other) const
		{
			return (_core_value == other.value());
		}

		___nodiscard___ bool operator!=(const pxmpc16& other) const
		{
			return (_core_value != other.value());
		}

	private:
		uint16_t _core_value = 0;
	};

	template <typename T>
	struct is_valid_pxm_pixel_channel_type
	{
		static ___constexpr___ const bool value = false;
	};

	template <>
	struct is_valid_pxm_pixel_channel_type<pxmpc8>
	{
		static ___constexpr___ const bool value = true;
	};

	template <>
	struct is_valid_pxm_pixel_channel_type<pxmpc10>
	{
		static ___constexpr___ const bool value = true;
	};

	template <>
	struct is_valid_pxm_pixel_channel_type<pxmpc12>
	{
		static ___constexpr___ const bool value = true;
	};

	template <>
	struct is_valid_pxm_pixel_channel_type<pxmpc14>
	{
		static ___constexpr___ const bool value = true;
	};

	template <>
	struct is_valid_pxm_pixel_channel_type<pxmpc16>
	{
		static ___constexpr___ const bool value = true;
	};

	struct pxmrgb 
	{ 
		static ___constexpr___ const uint16_t channels = 3;
	};

	struct pxmrgba 
	{
		static ___constexpr___ const uint16_t channels = 4;
	};

	template <typename T>
	struct is_valid_pxm_pixel_format_type
	{
		static ___constexpr___ const bool value = false;
	};

	template <>
	struct is_valid_pxm_pixel_format_type<pxmrgb>
	{
		static ___constexpr___ const bool value = true;
	};

	template <>
	struct is_valid_pxm_pixel_format_type<pxmrgba>
	{
		static ___constexpr___ const bool value = true;
	};

	template <typename _pxmfmt_t, typename _pxmpc_t>
	class pxm_pixel final
	{
	public:
		static_assert(is_valid_pxm_pixel_format_type<_pxmfmt_t>::value, "Invalid pxm pixel format type!");
		static_assert(is_valid_pxm_pixel_channel_type<_pxmpc_t>::value, "Invalid pxm pixel channel type!");

		typedef _pxmfmt_t pxm_pixel_format_type;
		typedef _pxmpc_t  pxm_pixel_channel_type;

	public:
		___constexpr20___ pxm_pixel() noexcept
		{
			_create_pixel();
		}

		___constexpr20___ pxm_pixel(pxm_pixel_channel_type* const pixel_data_begin, pxm_pixel_channel_type* const pixel_data_end)
		{
			if (static_cast<uint16_t>(pixel_data_end - pixel_data_begin) > _channels)
				throw std::invalid_argument("Pointer distance greater than acceptable pxm_pixel number of channels!");

			_create_pixel();

			for (pxm_pixel_channel_type* pixel_data_iterator = pixel_data_begin; pixel_data_iterator != pixel_data_end; ++pixel_data_iterator)
			{
				_push_back_const(*pixel_data_iterator);
			}
		}

		___constexpr20___ pxm_pixel(std::initializer_list<pxm_pixel_channel_type>&& pixel_data)
		{
			_create_pixel();

			_pack_pixel(std::move(pixel_data));
		}

		___constexpr20___ pxm_pixel(const pxm_pixel& other)
		{
			if (this == __builtin_addressof(other))
				throw std::exception("Self-assignment not allowed!");

			_create_pixel();

			pxm_pixel_channel_type* other_data = other.data();

			for (uint16_t i = 0; i < _channels; ++i)
			{
				_push_back_const(other_data[i]);
			}
		}

		___constexpr20___ pxm_pixel(pxm_pixel&& other) noexcept
		{
			_create_pixel();

			pxm_pixel_channel_type* other_data = other.data();

			for (uint16_t i = 0; i < _channels; ++i)
			{
				_push_back(std::move(other_data[i]));
			}
		}

		___constexpr20___ const pxm_pixel& operator=(const pxm_pixel& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			pxm_pixel_channel_type* other_data = other.data();

			_revert_inserter();

			for (uint16_t i = 0; i < _channels; ++i)
				_push_back_const(other_data[i]);
		
			return *this;
		}

		___constexpr20___ const pxm_pixel& operator=(pxm_pixel&& other) noexcept
		{
			if (*this == other)
				return *this;

			pxm_pixel_channel_type* other_data = other.data();

			_revert_inserter();

			for (uint16_t i = 0; i < _channels; ++i)
				_push_back(std::move(other_data[i]));
			
			return *this;
		}

		___constexpr20___ ~pxm_pixel() noexcept
		{
			_destroy_pixel();
		}

		___nodiscard___ ___constexpr20___ pxm_pixel_channel_type* data() const
		{
			return _core;
		}

		___nodiscard___ ___constexpr20___ uint16_t channels() const
		{
			return _channels;
		}

		___nodiscard___ ___constexpr20___ uint16_t size_bytes() const
		{
			return (_channels * sizeof(pxm_pixel_channel_type));
		}

		___nodiscard___ ___constexpr20___ bool operator!=(const pxm_pixel& other) const
		{
			pxm_pixel_channel_type* other_data = other.data();

			for (uint16_t i = 0; i < _channels; ++i)
			{
				if (_core[i] != other_data[i])
					return true;
			}

			return false;
		}

		___nodiscard___ ___constexpr20___ bool operator==(const pxm_pixel& other) const
		{
			return !(this->operator!=(other));
		}

	private:
		___constexpr20___ void _destroy_pixel()
		{
			if (_core != nullptr)
			{
				if (_inserter != (_core + _channels))
					_inserter = (_core + _channels);

				while (_inserter != _core)
				{
					--_inserter;
					_inserter->~pxm_pixel_channel_type();
				}

				::operator delete(reinterpret_cast<void*>(_core), (_channels * sizeof(pxm_pixel_channel_type)));

				_core = nullptr;
				_inserter = nullptr;
			}
		}

		___constexpr20___ void _create_pixel()
		{
			_destroy_pixel();

			_core = reinterpret_cast<pxm_pixel_channel_type*>(::operator new(_channels * sizeof(pxm_pixel_channel_type)));
			_inserter = _core;
		}

		___constexpr20___ void _push_back_const(const pxm_pixel_channel_type& pixel_value)
		{
			if (_inserter != (_core + _channels))
			{
				::new(_inserter) pxm_pixel_channel_type(pixel_value);

				++_inserter;
			}
		}

		___constexpr20___ void _push_back(pxm_pixel_channel_type&& pixel_value)
		{
			if (_inserter != (_core + _channels))
			{
				::new(_inserter) pxm_pixel_channel_type(std::move(pixel_value));

				++_inserter;
			}
		}

		___constexpr20___ void _pack_pixel(std::initializer_list<pxm_pixel_channel_type>&& pixel_data)
		{
			for (const pxm_pixel_channel_type* pixel_data_iterator = pixel_data.begin(); pixel_data_iterator != pixel_data.end(); ++pixel_data_iterator)
			{
				_push_back_const(*pixel_data_iterator);
			}
		}

		___constexpr20___ void _revert_inserter()
		{
			if (_inserter != _core) _inserter = _core;
		}

	private:
		pxm_pixel_channel_type* _core = nullptr;
		const uint16_t _channels = std::conditional<std::is_same_v<pxm_pixel_format_type, pxmrgb>, pxmrgb, pxmrgba>::type::channels;
		pxm_pixel_channel_type* _inserter = nullptr;
	};

	template <typename _pxmfmt_t, typename _pxmpc_t>
	class pxm_matrix final
	{
	public:
		static_assert(is_valid_pxm_pixel_format_type<_pxmfmt_t>::value, "Invalid pxm pixel format type!");
		static_assert(is_valid_pxm_pixel_channel_type<_pxmpc_t>::value, "Invalid pxm pixel channel type!");

		typedef pxm_pixel<_pxmfmt_t, _pxmpc_t> pixel_type;
		typedef pixel_type*					   matrix_pointer;
		typedef const pixel_type&			   const_lvalue_reference;
		typedef pixel_type&					   lvalue_reference;
		typedef pixel_type&&				   rvalue_reference;

	public:
		___constexpr20___ pxm_matrix() noexcept = default;

		___constexpr20___ pxm_matrix(const uint32_t height, const uint32_t width)
		{
			_allocate(height, width);
		}

		___constexpr20___ pxm_matrix(const pxm_matrix& other)
		{
			if (this == __builtin_addressof(other))
				throw std::invalid_argument("Self-assignment not allowed!");

			_allocate(other.rows(), other.cols());

			for (uint64_t i = 0; i < _absolute_size(); ++i)
			{
				_push_const(other[i]);
			}
		}

		___constexpr20___ pxm_matrix(pxm_matrix&& other) noexcept
		{
			_allocate(other.rows(), other.cols());

			for (uint64_t i = 0; i < _absolute_size(); ++i)
			{
				_push(std::move(other[i]));
			}
		}

		___constexpr20___ const pxm_matrix& operator=(const pxm_matrix& other)
		{
			if (this == __builtin_addressof(other))
				return *this;

			if (_empty())
			{
				_allocate(other.rows(), other.cols());

				for (uint64_t i = 0; i < _absolute_size(); ++i)
				{
					_push_const(other[i]);
				}
			}

			else if ((_rows != other.rows()) || (_columns != other.cols()))
			{
				_deallocate();

				_allocate(other.rows(), other.cols());

				for (uint64_t i = 0; i < _absolute_size(); ++i)
				{
					_push_const(other[i]);
				}
			}

			else
			{
				for (uint64_t i = 0; i < _absolute_size(); ++i)
				{
					_core[i] = other[i];
				}
			}

			return *this;
		}

		___constexpr20___ const pxm_matrix& operator=(pxm_matrix&& other) noexcept
		{
			if (*this == other)
				return *this;

			if (_empty())
			{
				_allocate(other.rows(), other.cols());

				for (uint64_t i = 0; i < _absolute_size(); ++i)
				{
					_push(std::move(other[i]));
				}
			}

			else if ((_rows != other.rows()) || (_columns != other.cols()))
			{
				_deallocate();
				
				_allocate(other.rows(), other.cols());

				for (uint64_t i = 0; i < _absolute_size(); ++i)
				{
					_push(std::move(other[i]));
				}
			}
			
			else
			{
				for (uint64_t i = 0; i < _absolute_size(); ++i)
				{
					_core[i] = std::move(other[i]);
				}
			}

			return *this;
		}

		___constexpr20___ ~pxm_matrix()
		{
			if (!_empty())
			{
				_deallocate();
			}
		}

		___nodiscard___ ___constexpr20___ matrix_pointer data() const
		{
			return _core;
		}

		___nodiscard___ ___constexpr20___ uint32_t rows() const
		{
			return _rows;
		}

		___nodiscard___ ___constexpr20___ uint32_t cols() const
		{
			return _columns;
		}

		___nodiscard___ ___constexpr20___ uint64_t size() const
		{
			return _absolute_size();
		}

		___nodiscard___ ___constexpr20___ const_lvalue_reference operator[](const uint64_t position) const
		{
			if (_empty())
				throw std::exception("Can not index empty matrix!");

			if (position >= _absolute_size())
				throw std::out_of_range("Index out of matrix bounds!");

			return _core[position];
		}

		___nodiscard___ ___constexpr20___ lvalue_reference operator[](const uint64_t position)
		{
			if (_empty())
				throw std::exception("Can not index empty matrix!");

			if (position >= _absolute_size())
				throw std::out_of_range("Index out of matrix bounds!");

			return _core[position];
		}

		___nodiscard___ ___constexpr20___ const_lvalue_reference operator()(const uint32_t outer_position, const uint32_t inner_position) const
		{
			if (_empty())
				throw std::exception("Can not index empty matrix!");

			if ((outer_position >= _rows) || (inner_position >= _columns))
				throw std::out_of_range("Index or indices out of matrix bounds!");

			return _get_at_const(outer_position, inner_position);
		}

		___nodiscard___ ___constexpr20___ lvalue_reference operator()(const uint32_t outer_position, const uint32_t inner_position)
		{
			if (_empty())
				throw std::exception("Can not index empty matrix!");

			if ((outer_position >= _rows) || (inner_position >= _columns))
				throw std::out_of_range("Index or indices out of matrix bounds!");

			return _get_at(outer_position, inner_position);
		}

		___nodiscard___ ___constexpr20___ bool empty() const
		{
			return _empty();
		}

		___constexpr20___ void push(const_lvalue_reference pixel_value)
		{
			if (_empty())
				throw std::exception("Matrix is empty!");

			_push_const(pixel_value);
		}

		___constexpr20___ void push(rvalue_reference pixel_value) noexcept(false)
		{
			if (_empty())
				throw std::exception("Matrix is empty!");

			_push(std::move(pixel_value));
		}

		___constexpr20___ void new_matrix(const uint32_t height, const uint32_t width)
		{
			if(!_empty())
				_deallocate();

			_allocate(height, width);
		}

		___constexpr20___ void clear()
		{
			if (!_empty())
				_deallocate();

			else throw std::exception("Can not clear empty matrix!");
		}

		___nodiscard___ ___constexpr20___ bool operator!=(const pxm_matrix& other) const
		{
			if ((_rows != other.rows()) || (_columns != other.cols()))
				return true;

			for (uint64_t i = 0; i < _absolute_size(); ++i)
			{
				if (_core[i] != other[i])
					return true;
			}

			return false;
		}

		___nodiscard___ ___constexpr20___ bool operator==(const pxm_matrix& other) const
		{
			return !(this->operator!=(other));
		}


	private:
		___constexpr20___ void _allocate(const uint32_t height, const uint32_t width)
		{
			_rows = height;
			_columns = width;

			_core = reinterpret_cast<matrix_pointer>(::operator new((_absolute_size() * sizeof(pixel_type))));

			_inserter = _core;
		}

		___constexpr20___ void _deallocate()
		{
			while (_inserter != _core)
			{
				--_inserter;

				_inserter->~pxm_pixel();
			}

			_inserter = nullptr;

			::operator delete(reinterpret_cast<void*>(_core), (_absolute_size() * sizeof(pixel_type)));

			_rows = 0;
			_columns = 0;
		}

		___constexpr20___ void _push_const(const_lvalue_reference pixel_value) noexcept
		{
			if (_inserter != (_core + _absolute_size()))
			{
				::new(_inserter) pixel_type(pixel_value);

				++_inserter;
			}
		}

		___constexpr20___ void _push(rvalue_reference pixel_value) noexcept
		{
			if (_inserter != (_core + _absolute_size()))
			{
				::new(_inserter) pixel_type(std::move(pixel_value));

				++_inserter;
			}
		}

		___nodiscard___ ___constexpr20___ const_lvalue_reference _get_at_const(const uint32_t outer_position, const uint32_t inner_position) const
		{
			return *(_core + (static_cast<uint64_t>(inner_position) + (static_cast<uint64_t>(outer_position) * static_cast<uint64_t>(_columns))));
		}

		___nodiscard___ ___constexpr20___ lvalue_reference _get_at(const uint32_t outer_position, const uint32_t inner_position)
		{
			return *(_core + (static_cast<uint64_t>(inner_position) + (static_cast<uint64_t>(outer_position) * static_cast<uint64_t>(_columns))));
		}

		___nodiscard___ ___constexpr20___ uint64_t _absolute_size() const
		{
			return (static_cast<uint64_t>(_rows) * static_cast<uint64_t>(_columns));
		}

		___nodiscard___ ___constexpr20___ bool _empty() const
		{
			return ((_core == nullptr) && (_rows == 0) && (_columns == 0) && (_inserter == nullptr));
		}

	private:
		matrix_pointer _core = nullptr;
		uint32_t _rows = 0;
		uint32_t _columns = 0;
		matrix_pointer _inserter = nullptr;
	};
}

#endif /* _PXM_PRIMITIVES_ */