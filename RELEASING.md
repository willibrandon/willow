# Releasing Willow

## Automated Release Process

Willow uses GitHub Actions for automated releases. Simply tag and push:

```bash
git tag v0.2.0
git push origin v0.2.0
```

This triggers:
1. Package validation and creation (tar.gz and zip)
2. GitHub release with artifacts
3. PR submission to zed-industries/extensions

## Manual Release

If needed, you can run the release process manually:

```bash
# Package the extension
./scripts/release.sh 0.2.0

# Submit to Zed (requires GitHub CLI)
./scripts/submit-to-zed.sh 0.2.0
```

## Pre-release Checklist

- [ ] Test extension in Zed
- [ ] Verify all language injections work
- [ ] Update VERSION file
- [ ] Commit all changes
- [ ] Tag with semantic version (v0.2.0)


