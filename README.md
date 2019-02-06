## Notice
**This project is a sub-project of the napper-for-tpm and modified by Seunghun Han to check a TPM vulnerability, CVE-2018-6622.**
**If you want to build this project alone, please visit the main project, [Napper for TPM](https://www.github.com/kkamagui/napper-for-tpm)**

This site contains the code for the TPM (Trusted Platform Module) 2.0 tools based on TPM2.0-TSS.

Below is the name list of the implemented tools:

## Subset 0: TPM testing tools
tpm2\_getinfo
tpm2\_extendpcrs

## Subset 1: NV tools
tpm2\_nvdefine
tpm2\_nvrelease
tpm2\_nvread
tpm2\_nvreadlock
tpm2\_nvwrite
tpm2\_nvlist

## Subset 2: Attestation tools
tpm2\_takeownership
tpm2\_getpubek
tpm2\_getmanufec
tpm2\_getpubak
tpm2\_akparse
tpm2\_makecredential
tpm2\_activatecredential
tpm2\_listpcrs
tpm2\_quote
tpm2\_listpersistent

## Subset 3: Key management tools
tpm2\_createprimary
tpm2\_create
tpm2\_evictcontrol
tpm2\_load
tpm2\_loadexternal

## Subset 4: Encryption tools
tpm2\_encryptdecrypt
tpm2\_rsaencrypt
tpm2\_rsadecrypt
tpm2\_unseal

## Subset 5: Signing tools
tpm2\_sign
tpm2\_verifysignature
tpm2\_certify

## Subset 6: utilities
tpm2\_getrandom
tpm2\_hash
tpm2\_hmac
tpm2\_readpublic

## Build and Installation instructions:
Instructions for building and installing the tpm2.0-tools are provided in the [INSTALL](https://github.com/01org/tpm2.0-tools/blob/master/INSTALL) file.

**For more details on this code and how to use it, the [manual](https://github.com/01org/tpm2.0-tools/blob/master/manual) file is a good place to start.**

## Resources
TPM 2.0 specifications can be found at [Trusted Computing Group](http://www.trustedcomputinggroup.org/).

