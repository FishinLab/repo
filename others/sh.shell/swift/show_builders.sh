#!/bin/bash
printf "account-server status : \n"
swift-ring-builder /etc/swift/account.builder
printf "container-server status : \n"
swift-ring-builder /etc/swift/container.builder
printf "object-server status : \n"
swift-ring-builder /etc/swift/object.builder 
