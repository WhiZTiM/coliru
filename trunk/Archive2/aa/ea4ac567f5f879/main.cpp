// from vendor header file
extern "C" {

enum vendor_error_code {
    SUCCESS, ERROR
};

struct vendor_ptr_s {
    int int1; // values used in some internal datastructure
    int int2;
};
typedef struct vendor_ptr_s vendor_ptr_t;

vendor_error_code alloc_vendor_data(vendor_ptr_t*);
vendor_error_code free_vendor_data(vendor_ptr_t);

}

// my c++ wrapper class

class VendorWrapper {
private:
    vendor_ptr_t global_vendor_data;

public:
    VendorWrapper() {
        if (alloc_vendor_data(&global_vendor_data) != SUCCESS) {
            // throw exception
        }
    }
    
    ~VendorWrapper() {
        if (free_vendor_data(global_vendor_data) != SUCCESS) {
            // throw exception
        }
    }
    
    void foo() {
        vendor_ptr_t local_data1;
        if (alloc_vendor_data(&local_data1) != SUCCESS) {
            // throw excecption
        }
        vendor_ptr_t local_data2;
        if (alloc_vendor_data(&local_data2) != SUCCESS) {
            // throw excecption
        }

        // do something with local_data1 and local_data2

        free_vendor_data(local_data2);
        free_vendor_data(local_data1);
    }
};