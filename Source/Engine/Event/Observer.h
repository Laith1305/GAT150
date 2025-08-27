#pragma once
namespace viper {
	class IObserver {
		~IObserver() = default;

		virtual void OnNotify(const Event& event) = 0;
	};
}