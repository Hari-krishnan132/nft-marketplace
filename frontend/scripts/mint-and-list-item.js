const { ethers, network } = require("hardhat")
const { moveBlocks } = require("../utils/move-blocks")

const PRICE = ethers.utils.parseEther("0.1")
const tokenUri =
    "http://bafybeih7sgfhageprxr2lrg3sx5iejrqjkeoe2rxr5aj44y5qo6hv7viuq.ipfs.localhost:8081/"

async function mintAndList() {
    const nftMarketplace = await ethers.getContract("NftMarketplace")
    let basicNft

    basicNft = await ethers.getContract("BasicNft")

    console.log("Minting NFT...")
    const mintTx = await basicNft.mintNft(tokenUri)
    const mintTxReceipt = await mintTx.wait(1)
    const tokenId = mintTxReceipt.events[0].args.tokenId
    console.log("Approving NFT...")
    const approvalTx = await basicNft.approve(nftMarketplace.address, tokenId)
    await approvalTx.wait(1)
    console.log("Listing NFT...")
    const tx = await nftMarketplace.listItem(basicNft.address, tokenId, PRICE)
    await tx.wait(1)
    const tokenUriConfirmed = await basicNft.tokenURI(tokenId)
    console.log(`${tokenId} NFT Listed!`)
    console.log(`${tokenUriConfirmed}`)
    if (network.config.chainId == 31337) {
        await moveBlocks(1, (sleepAmount = 1000))
    }
}

mintAndList()
    .then(() => process.exit(0))
    .catch((error) => {
        console.error(error)
        process.exit(1)
    })
