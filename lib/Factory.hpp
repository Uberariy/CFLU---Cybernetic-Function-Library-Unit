/**
 * @file Factory.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CYBERNETIC_FACTORY_
#define CYBERNETIC_FACTORY_

#include <map>

#include "Function.hpp"

/* Factory */

class FunctionFactory {
    public:
        FunctionFactory() {
            RegisterAll();
        }

        class ICreator {
        public:
                virtual ~ICreator() {};
                virtual auto Create() -> std::shared_ptr<BaseFunction> const = 0;
                virtual auto Create(double param) -> std::shared_ptr<BaseFunction> const = 0;
                virtual auto Create(std::vector<double> params) -> std::shared_ptr<BaseFunction> const = 0;
        };

        template <class TFunction>
        class FunctionCreator : public ICreator {
        public:
            auto Create() -> std::shared_ptr<BaseFunction> const override {
                return std::make_shared<TFunction>(TFunction());
            }

            auto Create(double param) -> std::shared_ptr<BaseFunction> const override {
                return std::make_shared<TFunction>(TFunction(param));
            }

            auto Create(std::vector<double> params) -> std::shared_ptr<BaseFunction> const override {
                return std::make_shared<TFunction>(TFunction(params));
            }
        };

        std::vector<std::string> GetAvailableObjects() const {
            std::vector<std::string> RegisteredV;
            for (auto & [key, val]: RegisteredCreators) {
                RegisteredV.push_back(key);
            }
            return RegisteredV;
        }

        std::shared_ptr<BaseFunction> Create(const std::string& type) {
            return RegisteredCreators[type] -> Create();
        }

        std::shared_ptr<BaseFunction> Create(const std::string& type, double param) {
            return RegisteredCreators[type] -> Create(param);
        }
        
        std::shared_ptr<BaseFunction> Create(const std::string& type, std::vector<double> params) {
            return RegisteredCreators[type] -> Create(params);
        }
    private:
        using TCreatorPtr = std::shared_ptr<ICreator>;
        using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
        TRegisteredCreators RegisteredCreators;

        void RegisterAll() {
            RegisteredCreators["ident"] = std::make_shared<FunctionCreator<Identical>>();
            RegisteredCreators["const"] = std::make_shared<FunctionCreator<Constant>>();
            RegisteredCreators["power"] = std::make_shared<FunctionCreator<Power>>();
            RegisteredCreators["exp"] = std::make_shared<FunctionCreator<Exponential>>();
            RegisteredCreators["polynomial"] = std::make_shared<FunctionCreator<Polynomial>>();
        }

};

#endif