# Examples for EpicChainCpp

# Basic wallet example
add_executable(wallet_example wallet_example.cpp)
target_link_libraries(wallet_example PRIVATE epicchaincpp)

# Transaction example
add_executable(transaction_example transaction_example.cpp)
target_link_libraries(transaction_example PRIVATE epicchaincpp)

# Crypto example
add_executable(crypto_example crypto_example.cpp)
target_link_libraries(crypto_example PRIVATE epicchaincpp)