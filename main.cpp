#include <iostream>
#include "pxm.hpp"

int main()
{
	/*dt0::pxm_matrix<dt0::pxmrgb, dt0::pxmpc10> mat(2, 2);

	mat.push(std::move(dt0::pxm_pixel<dt0::pxmrgb, dt0::pxmpc10>({ 1023, 1023, 1023 })));
	mat.push(std::move(dt0::pxm_pixel<dt0::pxmrgb, dt0::pxmpc10>({ 0, 0, 0 })));
	mat.push(std::move(dt0::pxm_pixel<dt0::pxmrgb, dt0::pxmpc10>({ 511, 511, 511 })));
	mat.push(std::move(dt0::pxm_pixel<dt0::pxmrgb, dt0::pxmpc10>({ 1023, 1023, 1023 })));

	dt0::pxm_info info{ &mat, mat.rows(), mat.cols(), dt0::pxmrgb::channels, 10 };
	
	dt0::pxm<dt0::pxmrgb, dt0::pxmpc10> output;

	output.write("square2x2.pxm", info);*/

	try
	{
		dt0::pxm_ptr img = dt0::get_pxm_container("square2x2.pxm");

		if (img == nullptr)
			std::cerr << "Could not get pxm container!\n\n";

		std::cout << "File size: " << img->file_size_bytes() << " bytes\n" 
				  << "Data size: " << img->data_size_bytes() << " bytes\n"
				  << "Image height: " << img->height_pixels() << " px\n" 
				  << "Image width: " << img->width_pixels() << " px\n"
				  << "Pixel channels: " << img->pixel_channels() << '\n'
				  << "Pixel size bits: " << img->pixel_size_bits() << " bits\n"
				  << "Pixel channel size bits: " << img->pixel_channel_size_bits() << " bits\n\n";

		dt0::pxm_matrix<dt0::pxmrgb, dt0::pxmpc10> mat = dt0::pxm_matrix_cast<dt0::pxmrgb, dt0::pxmpc10>(img);

		std::cout << std::hex;

		for (uint32_t i = 0; i < mat.rows(); ++i)
		{
			for (uint32_t j = 0; j < mat.cols(); ++j)
			{
				auto ptr = mat(i, j).data();

				for (uint16_t c = 0; c < img->pixel_channels(); ++c)
				{
					std::cout << ptr[i].value() << ' ';
				}

				std::cout << "  ";
			}

			std::cout << '\n';
		}
	}

	catch (std::exception err)
	{
		std::cout << err.what();
	}

	return 0;
}