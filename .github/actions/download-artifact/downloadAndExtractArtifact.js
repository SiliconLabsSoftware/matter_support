const core = require('@actions/core');
const github = require('@actions/github');
const fs = require('fs');
const unzipper = require('unzipper');

async function downloadAndExtractArtifact(artifactName, downloadPath, filePath, provisioningRepo, branch, githubToken) {
  try {
    const octokit = github.getOctokit(githubToken);
    // List all artifacts for the specified repository and branch
    const artifacts = await octokit.rest.actions.listArtifactsForRepo({
      owner: github.context.repo.owner,
      repo: provisioningRepo,
      ref: branch
    });

    // Filter and sort artifacts by name and creation date
    const filteredArtifacts = artifacts.data.artifacts
      .filter(a => a.name === artifactName)
      .sort((a, b) => new Date(b.created_at) - new Date(a.created_at));

    // Check if the artifact exists
    if (filteredArtifacts.length === 0) {
      core.setFailed(`Artifact ${artifactName} not found`);
      return;
    }

    const latestArtifact = filteredArtifacts[0];

    // Download the latest artifact
    const { data: artifactData } = await octokit.rest.actions.downloadArtifact({
      owner: github.context.repo.owner,
      repo: provisioningRepo,
      artifact_id: latestArtifact.id,
      archive_format: 'zip'
    });

    // Create the download directory if it doesn't exist
    fs.mkdirSync(downloadPath, { recursive: true });
    // Save the downloaded artifact as a zip file
    fs.writeFileSync(filePath, Buffer.from(artifactData));

    // Extract the zip file to the specified download path
    fs.createReadStream(filePath)
      .pipe(unzipper.Extract({ path: downloadPath }))
      .on('close', () => {
        console.log(`Downloaded and extracted ${artifactName} to ${downloadPath}`);
        // Delete the zip file after extraction
        fs.unlinkSync(filePath);
      })
      .on('error', (error) => {
        console.error(`Error extracting ${artifactName}:`, error);
        core.setFailed(`Failed to extract ${artifactName}: ${error.message}`);
      });
  } catch (error) {
    // Set the action as failed if an error occurs
    core.setFailed(error.message);
  }
}

module.exports = { downloadAndExtractArtifact };