const core = require('@actions/core');
const { downloadAndExtractArtifact } = require('./downloadAndExtractArtifact');

async function run() {
  try {
    // Get inputs from the workflow file
    const artifactName = core.getInput('artifact-name');
    const downloadPath = core.getInput('download-path');
    const filePath = core.getInput('file-path');
    const provisioningRepo = core.getInput('provisioning-repo');
    const branch = core.getInput('branch');

    // Download and extract the artifact
    await downloadAndExtractArtifact(artifactName, downloadPath, filePath, provisioningRepo, branch);
  } catch (error) {
    // Set the action as failed if an error occurs
    core.setFailed(error.message);
  }
}

// Execute the run function
run();
