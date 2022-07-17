const { storeImages, storeTokeUriMetadata } = require("../utils/uploadToPinata")
const imagesLocation = "./images1/"

const metadataTemplate = {
    name: "",
    description: "",
    image: "",
    attributes: [
        {
            EncryptedCertificate: "",
        },
    ],
}

async function uploadPinata(filepath) {
    tokenUris = []
    jsons = []
    const { responses: imageUploadResponses, files } = await storeImages(filepath)
    for (imageUploadResponseIndex in imageUploadResponses) {
        let tokenUriMetadata = { ...metadataTemplate }
        tokenUriMetadata.name = files[imageUploadResponseIndex].replace(/.png|.jpg/gi, "")
        tokenUriMetadata.description = `${tokenUriMetadata.name} Stock`
        tokenUriMetadata.image = `ipfs://${imageUploadResponses[imageUploadResponseIndex].IpfsHash}`
        console.log(`Uploading ${tokenUriMetadata.name}...`)
        const metadataUploadResponse = await storeTokeUriMetadata(tokenUriMetadata)
        tokenUris.push(`ipfs://${metadataUploadResponse.IpfsHash}`)
    }
    console.log("Token URIs uploaded! They are:")
    console.log(tokenUris)
    return tokenUris
}

uploadPinata(imagesLocation)
    .then(() => process.exit(0))
    .catch((error) => {
        console.error(error)
        process.exit(1)
    })
