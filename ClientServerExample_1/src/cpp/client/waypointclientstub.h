/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_WAYPOINTCLIENTSTUB_H_
#define JSONRPC_CPP_STUB_WAYPOINTCLIENTSTUB_H_

#include <jsonrpccpp/client.h>

class waypointclientstub : public jsonrpc::Client
{
    public:
        waypointclientstub(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        bool addWaypoint(double param1, double param2, double param3, const std::string& param4) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            p.append(param2);
            p.append(param3);
            p.append(param4);
            Json::Value result = this->CallMethod("addWaypoint",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool removeWaypoint(const std::string& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            Json::Value result = this->CallMethod("removeWaypoint",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        bool modifyWaypoint(double param1, double param2, double param3, const std::string& param4) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            p.append(param2);
            p.append(param3);
            p.append(param4);
            Json::Value result = this->CallMethod("modifyWaypoint",p);
            if (result.isBool())
                return result.asBool();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        void saveJsonFile(const std::string& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            this->CallNotification("saveJsonFile",p);
        }
        std::string calcDistAndBear(const std::string& param1, const std::string& param2) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            p.append(param2);
            Json::Value result = this->CallMethod("calcDistAndBear",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        Json::Value getList() throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p = Json::nullValue;
            Json::Value result = this->CallMethod("getList",p);
            if (result.isArray())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        void removeAllVec() throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p = Json::nullValue;
            this->CallNotification("removeAllVec",p);
        }
        Json::Value getWaypoint(const std::string& param1) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p.append(param1);
            Json::Value result = this->CallMethod("getWaypoint",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_WAYPOINTCLIENTSTUB_H_
