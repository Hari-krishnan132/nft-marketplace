// SPDX-License-Identifier: MIT
pragma solidity ^0.8.7;

import "@openzeppelin/contracts/token/ERC721/extensions/ERC721URIStorage.sol";

contract BasicNft is ERC721URIStorage {
    mapping(uint256 => string) s_tokenIdtoUri;
    uint256 private s_tokenCounter;

    event NftMinted(uint256 indexed tokenId);

    constructor() ERC721("Stock", "STK") {
        s_tokenCounter = 0;
    }

    function mintNft(string memory uriStr) public {
        uint256 newItemId = s_tokenCounter;
        s_tokenCounter = s_tokenCounter + 1;
        s_tokenIdtoUri[newItemId] = uriStr;
        _safeMint(msg.sender, newItemId);
        _setTokenURI(newItemId, s_tokenIdtoUri[newItemId]);
        emit NftMinted(newItemId);
    }

    function tokenURI(uint256 tokenId) public view override returns (string memory) {
        require(_exists(tokenId), "ERC721Metadata: URI query for nonexistent token");
        return s_tokenIdtoUri[tokenId];
    }

    function getTokenCounter() public view returns (uint256) {
        return s_tokenCounter;
    }
}
