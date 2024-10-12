#include <momo/javascript_interface.hpp>

using namespace momo::javascript;

void print_hello_world()
{
	puts("Hello World");
}

javascript_value print_string_array(const std::vector<javascript_value>& arguments)
{
	if (arguments.size() != 1)
	{
		return false;
	}

	const auto array = arguments[0];
	const auto values = array.get_elements();

	for (const auto& value : values)
	{
		puts(value.as<std::string>().c_str());
	}

	return true;
}

javascript_value run_js_function(const javascript_value& this_value, const std::vector<javascript_value>& arguments)
{
	if (arguments.size() != 1)
	{
		return false;
	}

	const auto func = arguments[0];

	(void)func(this_value, "Hello from C++");

	return true;
}

javascript_value initialize_javascript_module(javascript_interface& js, const javascript_value& exports)
{
	puts("Initializing module...");

	exports.set_property("hello_world", js.create_function(print_hello_world));
	exports.set_property("print_string_array", js.create_function(print_string_array));
	exports.set_property("run_js_function", js.create_function(run_js_function));

	return exports;
}

REGISTER_JAVASCRIPT_MODULE(initialize_javascript_module)
