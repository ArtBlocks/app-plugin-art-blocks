# Badges
[![Code style check](https://github.com/blooo-io/LedgerHQ-app-plugin-art-blocks/actions/workflows/lint-workflow.yml/badge.svg?branch=main)](https://github.com/blooo-io/LedgerHQ-app-plugin-art-blocks/actions/workflows/lint-workflow.yml)
[![Compilation & tests](https://github.com/blooo-io/LedgerHQ-app-plugin-art-blocks/actions/workflows/ci-workflow.yml/badge.svg?branch=main)](https://github.com/blooo-io/LedgerHQ-app-plugin-art-blocks/actions/workflows/ci-workflow.yml)
# LedgerHQ-app-plugin-art-blocks
Art Blocks Plugin

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a NFT transaction.
## Prerequisite

Clone the plugin to a new folder.

```shell
git clone https://github.com/blooo-io/LedgerHQ-app-plugin-art-blocks.git
```

Then in the same folder clone two more repositories, which is the plugin-tools and app-ethereum.

```shell
git clone https://github.com/LedgerHQ/plugin-tools.git                          #plugin-tools
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git     #app-ethereum
```
## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.asc).

## Smart Contracts

Smart contracts covered by this plugin are:

| Network | Version | Smart Contract |
| ---      | --- | --- |
| Ethereum | V0.8.9 | `0x48742D38a0809135EFd643c1150BfC13768C3907`|


## Build

Go to the plugin-tools folder and run the "./start" script.
```shell
cd plugin-tools  # go to plugin folder
./start.sh       # run the script start.sh
```
The script will build a docker image and attach a console.
When the docker image is running go to the "LedgerHQ-app-plugin-art-blocks" folder and build the ".elf" files.
```shell
cd LedgerHQ-app-plugin-art-blocks/tests       # go to the tests folder in LedgerHQ-app-plugin-art-blocks
./build_local_test_elfs.sh      # run the script build_local_test_elfs.sh
```

## Tests

To test the plugin go to the tests folder from the "LedgerHQ-app-plugin-art-blocks" and run the script "test"
```shell
cd LedgerHQ-app-plugin-art-blocks/tests       # go to the tests folder in LedgerHQ-app-plugin-art-blocks
yarn test                       # run the script test
```
## Continuous Integration


The flow processed in [GitHub Actions](https://github.com/features/actions) is the following:

- Code formatting with [clang-format](http://clang.llvm.org/docs/ClangFormat.html)
- Compilation of the application for Ledger Nano S in [ledger-app-builder](https://github.com/LedgerHQ/ledger-app-builder)
