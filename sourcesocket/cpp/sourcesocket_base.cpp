
#include "sourcesocket_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY
    
 	Source: sourcesocket.spd.xml
 	Generated on: Fri Jun 28 14:59:23 EDT 2013
 	REDHAWK IDE
 	Version: 1.8.4
 	Build id: R201305151907

*******************************************************************************************/

/******************************************************************************************

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/
 
sourcesocket_base::sourcesocket_base(const char *uuid, const char *label) :
                                     Resource_impl(uuid, label), serviceThread(0) {
    construct();
}

void sourcesocket_base::construct()
{
    Resource_impl::_started = false;
    loadProperties();
    serviceThread = 0;
    
    PortableServer::ObjectId_var oid;
    dataOctet_out = new BULKIO_dataOctet_Out_i("dataOctet_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataOctet_out);
    dataChar_out = new BULKIO_dataChar_Out_i("dataChar_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataChar_out);
    dataShort_out = new BULKIO_dataShort_Out_i("dataShort_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataShort_out);
    dataUshort_out = new BULKIO_dataUshort_Out_i("dataUshort_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataUshort_out);
    dataUlong_out = new BULKIO_dataUlong_Out_i("dataUlong_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataUlong_out);
    dataLong_out = new BULKIO_dataLong_Out_i("dataLong_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataLong_out);
    dataFloat_out = new BULKIO_dataFloat_Out_i("dataFloat_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataFloat_out);
    dataDouble_out = new BULKIO_dataDouble_Out_i("dataDouble_out", this);
    oid = ossie::corba::RootPOA()->activate_object(dataDouble_out);

    registerOutPort(dataOctet_out, dataOctet_out->_this());
    registerOutPort(dataChar_out, dataChar_out->_this());
    registerOutPort(dataShort_out, dataShort_out->_this());
    registerOutPort(dataUshort_out, dataUshort_out->_this());
    registerOutPort(dataUlong_out, dataUlong_out->_this());
    registerOutPort(dataLong_out, dataLong_out->_this());
    registerOutPort(dataFloat_out, dataFloat_out->_this());
    registerOutPort(dataDouble_out, dataDouble_out->_this());
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void sourcesocket_base::initialize() throw (CF::LifeCycle::InitializeError, CORBA::SystemException)
{
}

void sourcesocket_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    boost::mutex::scoped_lock lock(serviceThreadLock);
    if (serviceThread == 0) {
        serviceThread = new ProcessThread<sourcesocket_base>(this, 0.1);
        serviceThread->start();
    }
    
    if (!Resource_impl::started()) {
    	Resource_impl::start();
    }
}

void sourcesocket_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    boost::mutex::scoped_lock lock(serviceThreadLock);
    // release the child thread (if it exists)
    if (serviceThread != 0) {
        if (!serviceThread->release(2)) {
            throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
        }
        serviceThread = 0;
    }
    
    if (Resource_impl::started()) {
    	Resource_impl::stop();
    }
}

CORBA::Object_ptr sourcesocket_base::getPort(const char* _id) throw (CORBA::SystemException, CF::PortSupplier::UnknownPort)
{

    std::map<std::string, Port_Provides_base_impl *>::iterator p_in = inPorts.find(std::string(_id));
    if (p_in != inPorts.end()) {

    }

    std::map<std::string, CF::Port_var>::iterator p_out = outPorts_var.find(std::string(_id));
    if (p_out != outPorts_var.end()) {
        return CF::Port::_duplicate(p_out->second);
    }

    throw (CF::PortSupplier::UnknownPort());
}

void sourcesocket_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    // deactivate ports
    releaseInPorts();
    releaseOutPorts();

    delete(dataOctet_out);
    delete(dataChar_out);
    delete(dataShort_out);
    delete(dataUshort_out);
    delete(dataUlong_out);
    delete(dataLong_out);
    delete(dataFloat_out);
    delete(dataDouble_out);
 
    Resource_impl::releaseObject();
}

void sourcesocket_base::loadProperties()
{
    addProperty(connection_type,
                "server", 
               "connection_type",
               "",
               "readwrite",
               "",
               "external",
               "configure");

    addProperty(ip_address,
               "ip_address",
               "",
               "readwrite",
               "",
               "external",
               "configure");

    addProperty(port,
               "port",
               "",
               "readwrite",
               "",
               "external",
               "configure");

    addProperty(status,
               "status",
               "",
               "readonly",
               "",
               "external",
               "configure");

    addProperty(total_bytes,
               "total_bytes",
               "",
               "readonly",
               "",
               "external",
               "configure");

    addProperty(bytes_per_sec,
               "bytes_per_sec",
               "",
               "readonly",
               "",
               "external",
               "configure");

    addProperty(max_bytes,
                16384, 
               "max_bytes",
               "",
               "readwrite",
               "",
               "external",
               "configure");

    addProperty(min_bytes,
                16384, 
               "min_bytes",
               "",
               "readwrite",
               "",
               "external",
               "configure");

    addProperty(byte_swap,
                0, 
               "byte_swap",
               "",
               "readwrite",
               "",
               "external",
               "configure");

    addProperty(sri,
               "sri",
               "",
               "readwrite",
               "",
               "external",
               "configure");

}
