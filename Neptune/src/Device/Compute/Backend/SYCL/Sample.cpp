#include "Pchheader.h"

#ifdef NP_COMPUTE_SYCL

#include "Sample.h"

#include <CL/sycl.hpp>

namespace Neptune::SYCL {
	
	void Sample()
    {
        cl::sycl::queue q;

        NEPTUNE_LOG_CORE(I) << "SYCL Device: " << q.get_device().get_info<cl::sycl::info::device::name>();
    }
	
}

#endif