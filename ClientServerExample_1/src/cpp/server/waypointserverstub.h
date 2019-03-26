/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_WAYPOINTSERVERSTUB_H_
#define JSONRPC_CPP_STUB_WAYPOINTSERVERSTUB_H_

#include <jsonrpccpp/server.h>

class waypointserverstub : public jsonrpc::AbstractServer<waypointserverstub>
{
    public:
        waypointserverstub(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) : jsonrpc::AbstractServer<waypointserverstub>(conn, type)
        {
            this->bindAndAddMethod(jsonrpc::Procedure("addWaypoint", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_REAL,"param2",jsonrpc::JSON_REAL,"param3",jsonrpc::JSON_REAL,"param4",jsonrpc::JSON_STRING, NULL), &waypointserverstub::addWaypointI);
            this->bindAndAddMethod(jsonrpc::Procedure("removeWaypoint", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &waypointserverstub::removeWaypointI);
            this->bindAndAddMethod(jsonrpc::Procedure("modifyWaypoint", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_REAL,"param2",jsonrpc::JSON_REAL,"param3",jsonrpc::JSON_REAL,"param4",jsonrpc::JSON_STRING, NULL), &waypointserverstub::modifyWaypointI);
            this->bindAndAddNotification(jsonrpc::Procedure("saveJsonFile", jsonrpc::PARAMS_BY_POSITION, "param1",jsonrpc::JSON_STRING, NULL), &waypointserverstub::saveJsonFileI);
            this->bindAndAddMethod(jsonrpc::Procedure("calcDistAndBear", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &waypointserverstub::calcDistAndBearI);
            this->bindAndAddMethod(jsonrpc::Procedure("getList", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY,  NULL), &waypointserverstub::getListI);
            this->bindAndAddNotification(jsonrpc::Procedure("removeAllVec", jsonrpc::PARAMS_BY_POSITION,  NULL), &waypointserverstub::removeAllVecI);
            this->bindAndAddMethod(jsonrpc::Procedure("getWaypoint", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &waypointserverstub::getWaypointI);
        }

        inline virtual void addWaypointI(const Json::Value &request, Json::Value &response)
        {
            response = this->addWaypoint(request[0u].asDouble(), request[1u].asDouble(), request[2u].asDouble(), request[3u].asString());
        }
        inline virtual void removeWaypointI(const Json::Value &request, Json::Value &response)
        {
            response = this->removeWaypoint(request[0u].asString());
        }
        inline virtual void modifyWaypointI(const Json::Value &request, Json::Value &response)
        {
            response = this->modifyWaypoint(request[0u].asDouble(), request[1u].asDouble(), request[2u].asDouble(), request[3u].asString());
        }
        inline virtual void saveJsonFileI(const Json::Value &request)
        {
            this->saveJsonFile(request[0u].asString());
        }
        inline virtual void calcDistAndBearI(const Json::Value &request, Json::Value &response)
        {
            response = this->calcDistAndBear(request[0u].asString(), request[1u].asString());
        }
        inline virtual void getListI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->getList();
        }
        inline virtual void removeAllVecI(const Json::Value &request)
        {
            (void)request;
            this->removeAllVec();
        }
        inline virtual void getWaypointI(const Json::Value &request, Json::Value &response)
        {
            response = this->getWaypoint(request[0u].asString());
        }
        virtual bool addWaypoint(double param1, double param2, double param3, const std::string& param4) = 0;
        virtual bool removeWaypoint(const std::string& param1) = 0;
        virtual bool modifyWaypoint(double param1, double param2, double param3, const std::string& param4) = 0;
        virtual void saveJsonFile(const std::string& param1) = 0;
        virtual std::string calcDistAndBear(const std::string& param1, const std::string& param2) = 0;
        virtual Json::Value getList() = 0;
        virtual void removeAllVec() = 0;
        virtual Json::Value getWaypoint(const std::string& param1) = 0;
};

#endif //JSONRPC_CPP_STUB_WAYPOINTSERVERSTUB_H_
